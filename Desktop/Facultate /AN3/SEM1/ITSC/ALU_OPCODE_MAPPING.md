# ALU Opcode Mapping - CPU to ALU Translator

## Overview
This document describes the mapping between 6-bit CPU instruction opcodes and 4-bit ALU function codes (`alu_fn[3:0]`).

## ALU Function Code Structure

The 4-bit `alu_fn` is organized hierarchically:

```
alu_fn[3:0]
    |
    ├─ alu_fn[3]: Operation Category
    |              0 = Arithmetic Operations
    |              1 = Bitwise Operations
    |
    ├─ alu_fn[2]: Sub-category
    |              For Arithmetic (alu_fn[3]=0):
    |                  0 = Basic arithmetic (ADD, SUB, MUL, DIV)
    |                  1 = Extended arithmetic (MOD)
    |              For Bitwise (alu_fn[3]=1):
    |                  0 = Logic operations (AND, OR, XOR, NOT)
    |                  1 = Shift/Rotate operations (LSR, LSL, RSR, RSL)
    |
    └─ alu_fn[1:0]: Specific Operation Selection
                     Encoding depends on category and sub-category
```

## Complete Operation Mapping

### Arithmetic Operations (alu_fn[3] = 0)

| CPU Opcode | Operation | alu_fn[3:0] | Description |
|------------|-----------|-------------|-------------|
| 001010     | ADD       | 0000        | Addition |
| 001011     | SUB       | 0001        | Subtraction |
| 001100     | MUL       | 0010        | Multiplication |
| 001101     | DIV       | 0011        | Division |
| 001110     | MOD       | 0111        | Modulo (remainder) |

**Encoding Details:**
- `alu_fn[3] = 0` → Arithmetic
- `alu_fn[2] = 0` → Basic operations (ADD/SUB/MUL/DIV)
- `alu_fn[2] = 1` → Extended operation (MOD)
- `alu_fn[1:0]`:
  - `00` → ADD
  - `01` → SUB
  - `10` → MUL
  - `11` → DIV or MOD (distinguished by bit 2)

### Bitwise Logic Operations (alu_fn[3] = 1, alu_fn[2] = 0)

| CPU Opcode | Operation | alu_fn[3:0] | Description |
|------------|-----------|-------------|-------------|
| 010100     | OR        | 1000        | Bitwise OR |
| 010011     | AND       | 1001        | Bitwise AND |
| 010101     | XOR       | 1010        | Bitwise XOR |
| 010110     | NOT       | 1011        | Bitwise NOT (complement) |

**Encoding Details:**
- `alu_fn[3] = 1` → Bitwise
- `alu_fn[2] = 0` → Logic operations
- `alu_fn[1:0]`:
  - `00` → OR
  - `01` → AND
  - `10` → XOR
  - `11` → NOT

### Shift/Rotate Operations (alu_fn[3] = 1, alu_fn[2] = 1)

| CPU Opcode | Operation | alu_fn[3:0] | Description |
|------------|-----------|-------------|-------------|
| 001111     | LSR       | 1100        | Logical Shift Right |
| 010000     | LSL       | 1101        | Logical Shift Left |
| 010001     | RSR       | 1110        | Rotate Shift Right |
| 010010     | RSL       | 1111        | Rotate Shift Left |

**Encoding Details:**
- `alu_fn[3] = 1` → Bitwise
- `alu_fn[2] = 1` → Shift/Rotate operations
- `alu_fn[1:0]`:
  - `00` → LSR
  - `01` → LSL
  - `10` → RSR
  - `11` → RSL

## Control Signal: result_to_be_loaded

The `result_to_be_loaded` output indicates whether the ALU operation result should be stored:

- `1` → Result should be loaded (all ALU operations: arithmetic + bitwise)
- `0` → Result should NOT be loaded (control/memory operations: END, LD, ST, BRZ, MOV, CMP, etc.)

## Design Characteristics

### Structural Implementation
The module is implemented using **purely combinational logic** with **no behavioral constructs**:
- Uses only `assign` statements with boolean operations (AND, OR, NOT)
- No `always` blocks, `case` statements, or registers
- Fully synthesizable for FPGA/ASIC implementation

### Key Features
- **Combinational**: Zero propagation delay (async, gate-level)
- **Structural**: Built from wire assignments and logic gates
- **Hierarchical encoding**: Easy to decode in downstream ALU logic
- **Extensible**: Can add more operations by extending the encoding space

## Usage Example

```verilog
wire [5:0] cpu_opcode;
wire [3:0] alu_function;
wire       store_result;

cpu_to_alu_opcode_translator translator (
    .opcode(cpu_opcode),
    .alu_fn(alu_function),
    .result_to_be_loaded(store_result)
);

// Example: CPU sends ADD instruction
assign cpu_opcode = 6'b001010;  // CPU_OP_ADD
// translator outputs:
//   alu_fn = 4'b0000
//   result_to_be_loaded = 1'b1
```

## Decoding Logic for ALU

The ALU can decode operations efficiently:

```verilog
// Check operation category
wire is_arithmetic = ~alu_fn[3];
wire is_bitwise = alu_fn[3];

// Within arithmetic
wire is_basic_arith = is_arithmetic & ~alu_fn[2];
wire is_mod = is_arithmetic & alu_fn[2];

// Within bitwise
wire is_logic = is_bitwise & ~alu_fn[2];
wire is_shift = is_bitwise & alu_fn[2];

// Specific operation
wire is_add = is_basic_arith & (alu_fn[1:0] == 2'b00);
wire is_sub = is_basic_arith & (alu_fn[1:0] == 2'b01);
// ... etc
```

## Testing

All operations have been verified with the included testbench:
- 13 ALU operations tested
- 6 non-ALU operations tested
- 100% pass rate

Run tests with:
```bash
iverilog -o test cpu_to_alu_opcode_translator_tb.v cpu_to_alu_opcode_translator.v
vvp test
```
