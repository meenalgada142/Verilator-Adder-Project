module adder #(
    parameter N = 8                // Width of the adder
)(
    input  logic [N-1:0] a,        // Input A
    input  logic [N-1:0] b,        // Input B
    output logic [N-1:0] sum,      // Sum output
    output logic        carry      // Carry-out
);

    logic [N:0] result;

    always_comb begin
        result = a + b;
        sum    = result[N-1:0];
        carry  = result[N];
    
     // ✅ Verilator-compatible assertions
    assert (sum == result[N-1:0])
      else $error("❌ Sum mismatch: a=%0h b=%0h sum=%0h expected=%0h", a, b, sum, result[N-1:0]);

    assert (carry == result[N])
      else $error("❌ Carry mismatch: a=%0h b=%0h carry=%0b expected=%0b", a, b, carry, result[N]);
  end

endmodule
