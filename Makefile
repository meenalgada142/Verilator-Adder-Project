# Top-level module name
TOP_MODULE = adder

# Paths
RTL_DIR = rtl
SIM_DIR = sim
OBJ_DIR = obj_dir
VCD_FILE = dump.vcd

# Source files
RTL_SRC = $(RTL_DIR)/$(TOP_MODULE).sv
TB_SRC  = $(SIM_DIR)/testbench_adder.cpp

# Verilator flags
VERILATOR_FLAGS = -Wall --cc --trace --exe

# Default target
all: run

# Build simulation
$(OBJ_DIR)/V$(TOP_MODULE): $(RTL_SRC) $(TB_SRC)
	verilator $(VERILATOR_FLAGS) $(RTL_SRC) $(TB_SRC)
	make -C $(OBJ_DIR) -f V$(TOP_MODULE).mk

# Run simulation
run: $(OBJ_DIR)/V$(TOP_MODULE)
	./$(OBJ_DIR)/V$(TOP_MODULE)

# View waveform
wave:
	gtkwave $(VCD_FILE)

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(VCD_FILE)
