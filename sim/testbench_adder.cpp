#include "Vadder.h"              // Verilated model header for the DUT (adder.sv)
#include "verilated.h"           // Core Verilator functionality
#include "verilated_vcd_c.h"     // VCD waveform tracing support
#include <iostream>
#include <map>
#include <cstdlib>

// Simulation parameters
const int ADDER_WIDTH = 8;       // Bit-width of the adder
const int SIM_CYCLES  = 50;      // Total number of simulation cycles

// Transaction structure: defines input stimulus and expected output
struct AdderTransaction {
    int a;
    int b;
    int expected_sum;
    bool expected_carry;
};

// Driver: applies stimulus to the DUT
class AdderDriver {
public:
    Vadder* dut;
    AdderDriver(Vadder* d) : dut(d) {}
    void drive(const AdderTransaction& tr) {
        dut->a = tr.a;
        dut->b = tr.b;
    }
};

// Monitor: captures DUT outputs
class AdderMonitor {
public:
    Vadder* dut;
    AdderMonitor(Vadder* d) : dut(d) {}
    int get_sum()   { return dut->sum; }
    bool get_carry(){ return dut->carry; }
};

// Scoreboard: compares DUT output against expected values
class AdderScoreboard {
public:
    void check(int sum, bool carry, const AdderTransaction& tr, int cycle) {
        bool pass = (sum == tr.expected_sum) && (carry == tr.expected_carry);
        bool overflow = tr.expected_carry;
        bool wraparound = (sum < tr.a) || (sum < tr.b);

        std::cout << (pass ? "PASS" : "FAIL") << " - Cycle " << cycle
                  << ": " << tr.a << " + " << tr.b
                  << " = " << sum << " (Carry: " << carry << ")"
                  << " | Expected: " << tr.expected_sum << " (Carry: " << tr.expected_carry << ")";

        if (overflow)   std::cout << " [Overflow]";
        if (wraparound) std::cout << " [Wraparound]";
        std::cout << std::endl;
    }
};

// Coverage: tracks functional coverage metrics
class AdderCoverage {
public:
    std::map<int, int> sum_hits;
    int carry_0 = 0;
    int carry_1 = 0;
    int overflow_count = 0;
    int wraparound_count = 0;

    void sample(int sum, bool carry, const AdderTransaction& tr) {
        sum_hits[sum]++;
        carry ? carry_1++ : carry_0++;

        if (tr.expected_carry) overflow_count++;
        if ((sum < tr.a) || (sum < tr.b)) wraparound_count++;
    }

    void report() {
        std::cout << "\nFunctional Coverage Report:\n";
        for (int i = 0; i < (1 << ADDER_WIDTH); i++) {
            std::cout << "Sum " << i << ": " << sum_hits[i] << " hits" << std::endl;
        }
        std::cout << "Carry 0: " << carry_0 << " hits" << std::endl;
        std::cout << "Carry 1: " << carry_1 << " hits" << std::endl;
        std::cout << "Overflow cases: " << overflow_count << std::endl;
        std::cout << "Wraparound cases: " << wraparound_count << std::endl;
    }
};

// Required by Verilator for time tracking
double sc_time_stamp() { return 0; }

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vadder* dut = new Vadder;

    // Enable waveform tracing
    VerilatedVcdC* tfp = new VerilatedVcdC;
    Verilated::traceEverOn(true);
    dut->trace(tfp, 99);
    tfp->open("dump.vcd");

    // Instantiate testbench components
    AdderDriver driver(dut);
    AdderMonitor monitor(dut);
    AdderScoreboard scoreboard;
    AdderCoverage coverage;

    // Main simulation loop
    for (int cycle = 0; cycle < SIM_CYCLES; cycle++) {
        // Evaluate DUT before driving inputs
        dut->eval();
        tfp->dump(cycle * 2);

        // Generate random transaction
        AdderTransaction tr;
        tr.a = rand() % (1 << ADDER_WIDTH);
        tr.b = rand() % (1 << ADDER_WIDTH);
        int result = tr.a + tr.b;
        tr.expected_sum = result & ((1 << ADDER_WIDTH) - 1);
        tr.expected_carry = result >= (1 << ADDER_WIDTH);

        // Apply stimulus and evaluate DUT
        driver.drive(tr);
        dut->eval();
        tfp->dump(cycle * 2 + 1);

        // Capture and check outputs
        int sum = monitor.get_sum();
        bool carry = monitor.get_carry();
        scoreboard.check(sum, carry, tr, cycle);
        coverage.sample(sum, carry, tr);
    }

    // Final coverage report
    coverage.report();

    // Cleanup
    tfp->close();
    delete dut;
    return 0;
}
