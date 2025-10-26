# Verilator-Adder-Project

This project demonstrates a cycle-accurate simulation of an 8-bit adder using SystemVerilog and Verilator. It features a modular UVM-style testbench written in C++, showcasing industry-standard verification practices such as waveform tracing, scoreboarding, and functional coverage.

---

## 🧩 UVM-style Testbench Architecture

Although implemented in C++, the testbench mirrors Universal Verification Methodology (UVM) principles:

| UVM Concept         | C++ Equivalent     | Description                                      |
|---------------------|--------------------|--------------------------------------------------|
| `uvm_sequence_item` | `AdderTransaction` | Encapsulates stimulus (`a`, `b`) and expected outputs |
| `uvm_driver`        | `AdderDriver`      | Drives inputs to the DUT                         |
| `uvm_monitor`       | `AdderMonitor`     | Observes DUT outputs (`sum`, `carry`)            |
| `uvm_scoreboard`    | `AdderScoreboard`  | Compares DUT output with expected values         |
| `uvm_coverage`      | `AdderCoverage`    | Tracks functional coverage of sum and carry      |
| `uvm_env`           | `main()` function  | Instantiates and connects components             |
| `uvm_phase`         | Simulation loop    | Drives time-based stimulus and evaluation        |

This structure enables modularity, reusability, and clear separation of verification concerns.

---

## 🔧 Features

- Parameterized 8-bit adder module
- C++ testbench with:
  - Driver, Monitor, Scoreboard, Coverage
- Waveform tracing via `dump.vcd` for GTKWave analysis
- Coverage report for:
  - Sum values
  - Carry hits
  - Overflow and wraparound detection

---

## 📂 Directory Structure
```
Verilator-Adder-Project/
├── rtl/
│  └── adder.sv
├── sim/
│  └── testbench_adder.cpp
├── waveforms/
│  └── adder_waveform.png ├
── dump.vcd
├── Makefile
└── README.md

```
---

## ▶️ Build & Run Instructions

Make sure Verilator is installed and accessible in your terminal.

```bash
make clean   # Cleans build artifacts
make         # Builds and runs the simulation
```

## 🧪 Simulation Output
```
PASS - Cycle 0: 41 + 35 = 76 (Carry: 0)
PASS - Cycle 1: 190 + 132 = 66 (Carry: 1) [Overflow] [Wraparound]
...
PASS - Cycle 49: 145 + 157 = 46 (Carry: 1) [Overflow] [Wraparound]

```
## 📊 Coverage Summary

```
Carry 0: 26 hits
Carry 1: 24 hits
Overflow cases: 24
Wraparound cases: 24
Unique sum values hit: 66 / 256

```

---
## 👤 Author

**Meenal Gada**  
Transitioning from AC Power Application Engineering to ASIC Verification  
GitHub: [meenalgada142](https://github.com/meenalgada142)
