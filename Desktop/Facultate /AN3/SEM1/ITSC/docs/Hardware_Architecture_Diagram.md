# Arhitectura Hardware - Procesor 8-bit
## Diagramă Completă a Sistemului

```
                                    PROCESORUL 8-BIT - ARHITECTURA COMPLETĂ
    ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────┐
    │                                          CPU CORE                                                          │
    │                                                                                                            │
    │  ┌─────────────────────────────────────────────────────────────────────────────────────────────────────┐ │
    │  │                                    REGISTRE INTERNE                                                  │ │
    │  │                                                                                                     │ │
    │  │  ┌────────┐  ┌────────┐  ┌────────┐  ┌────────┐  ┌────────┐  ┌────────┐  ┌────────┐  ┌────────┐    │ │
    │  │  │   A    │  │   B    │  │   C    │  │   D    │  │   X    │  │   Y    │  │   SP   │  │   PC   │    │ │
    │  │  │ (8bit) │  │ (8bit) │  │ (8bit) │  │ (8bit) │  │ (8bit) │  │ (8bit) │  │ (8bit) │  │ (8bit) │    │ │
    │  │  └───┬────┘  └───┬────┘  └───┬────┘  └───┬────┘  └───┬────┘  └───┬────┘  └───┬────┘  └───┬────┘    │ │
    │  │      │           │           │           │           │           │           │           │         │ │
    │  └──────┼───────────┼───────────┼───────────┼───────────┼───────────┼───────────┼───────────┼─────────┘ │
    │         │           │           │           │           │           │           │           │           │
    │    ┌────┴─┐    ┌────┴─┐    ┌────┴─┐    ┌────┴─┐    ┌────┴─┐    ┌────┴─┐    ┌────┴─┐    ┌────┴─┐        │
    │    │ REG  │    │ REG  │    │ REG  │    │ REG  │    │ REG  │    │ REG  │    │ REG  │    │ REG  │        │
    │    │  A   │    │  B   │    │  C   │    │  D   │    │  X   │    │  Y   │    │  SP  │    │  PC  │        │
    │    │ FILE │    │ FILE │    │ FILE │    │ FILE │    │ FILE │    │ FILE │    │ FILE │    │ FILE │        │
    │    └────┬─┘    └────┬─┘    └────┬─┘    └────┬─┘    └────┬─┘    └────┬─┘    └────┬─┘    └────┬─┘        │
    │         │           │           │           │           │           │           │           │           │
    │         └─────────┬─┴───────────┴───────────┴───────────┴───────────┴───────────┼───────────┘           │
    │                   │                                                             │                       │
    │        ┌──────────▼──────────────────────────────────────────────────────────────▼─────────────┐        │
    │        │                              DATA BUS (8-bit)                                        │        │
    │        └──────────┬─────────────────────────────────────────────────────────────┬─────────────┘        │
    │                   │                                                             │                       │
    │  ┌────────────────▼─────────────────┐                            ┌──────────────▼────────────┐          │
    │  │            ALU (8-bit)           │                            │      FLAGS REGISTER       │          │
    │  │                                  │                            │                           │          │
    │  │  ┌─────────┐    ┌─────────┐     │                            │  ┌───┐ ┌───┐ ┌───┐ ┌───┐  │          │
    │  │  │ INPUT A │    │ INPUT B │     │                            │  │ Z │ │ C │ │ N │ │ V │  │          │
    │  │  │ (8-bit) │    │ (8-bit) │     │                            │  │   │ │   │ │   │ │   │  │          │
    │  │  └────┬────┘    └────┬────┘     │                            │  └───┘ └───┘ └───┘ └───┘  │          │
    │  │       │              │          │                            │  Zero  Carry Neg.  Ovfl   │          │
    │  │       └──────┬───────┘          │                            └───────────────────────────┘          │
    │  │              │                  │                                                                    │
    │  │    ┌─────────▼─────────┐        │                                                                    │
    │  │    │    OPERATION      │        │                                                                    │
    │  │    │     SELECTOR      │        │                                                                    │
    │  │    │     (4-bit)       │        │                                                                    │
    │  │    └─────────┬─────────┘        │                                                                    │
    │  │              │                  │                                                                    │
    │  │    ┌─────────▼─────────┐        │                                                                    │
    │  │    │                   │        │                                                                    │
    │  │    │   ARITHMETIC &    │        │                                                                    │
    │  │    │  LOGIC CIRCUITS   │        │                                                                    │
    │  │    │                   │        │                                                                    │
    │  │    │  ADD SUB AND OR   │        │                                                                    │
    │  │    │  XOR NOT SHL SHR  │        │                                                                    │
    │  │    │  INC DEC CMP      │        │                                                                    │
    │  │    └─────────┬─────────┘        │                                                                    │
    │  │              │                  │                                                                    │
    │  │    ┌─────────▼─────────┐        │                                                                    │
    │  │    │   RESULT OUTPUT   │        │                                                                    │
    │  │    │     (8-bit)       │        │                                                                    │
    │  │    └─────────┬─────────┘        │                                                                    │
    │  └──────────────┼──────────────────┘                                                                    │
    │                 │                                                                                       │
    │                 └───────────────┬───────────────────────────────────────────────────────────────────┐ │
    │                                 │                                                                   │ │
    │  ┌──────────────────────────────▼─────────────────────────────────────────────────────────────────┐ │ │
    │  │                                     CONTROL UNIT                                               │ │ │
    │  │                                                                                                │ │ │
    │  │  ┌────────────────┐  ┌─────────────────┐  ┌─────────────────┐  ┌──────────────────┐            │ │ │
    │  │  │   INSTRUCTION  │  │    INSTRUCTION  │  │     DECODER     │  │    MICROCODE     │            │ │ │
    │  │  │     FETCH      │  │     REGISTER    │  │                 │  │     GENERATOR    │            │ │ │
    │  │  │                │  │     (8-bit)     │  │   OPCODE (4)    │  │                  │            │ │ │
    │  │  │   PC -> ADDR   │  │                 │  │   OPERAND (4)   │  │  Control Signals │            │ │ │
    │  │  └────────────────┘  └─────────────────┘  └─────────────────┘  └──────────────────┘            │ │ │
    │  │                                                                                                │ │ │
    │  │  Control Signals Output:                                                                       │ │ │
    │  │  • ALU_OP[3:0]    - ALU Operation Select                                                      │ │ │
    │  │  • REG_WE        - Register Write Enable                                                      │ │ │
    │  │  • MEM_WE        - Memory Write Enable                                                        │ │ │
    │  │  • MEM_RE        - Memory Read Enable                                                         │ │ │
    │  │  • PC_WE         - Program Counter Write Enable                                               │ │ │
    │  │  • SP_WE         - Stack Pointer Write Enable                                                 │ │ │
    │  │  • FLAGS_WE      - Flags Register Write Enable                                                │ │ │
    │  └────────────────────────────────────────────────────────────────────────────────────────────┘ │ │
    │                                                                                                    │ │
    └────────────────────────────────────────────────────────────────────────────────────────────────────┘ │
                                                                                                             │
    ┌────────────────────────────────────────────────────────────────────────────────────────────────────┐ │
    │                                        MEMORY SYSTEM                                              │ │
    │                                                                                                    │ │
    │  ┌─────────────────────┐  ┌─────────────────────┐  ┌─────────────────────┐  ┌──────────────────┐   │ │
    │  │    PROGRAM ROM      │  │      DATA RAM       │  │       STACK         │  │    I/O PORTS     │   │ │
    │  │                     │  │                     │  │                     │  │                  │   │ │
    │  │  0x0000 - 0x00FF    │  │  0x0100 - 0x01DF    │  │  0x01E0 - 0x01FF    │  │ 0x0200 - 0x020F │   │ │
    │  │     (256 bytes)     │  │     (224 bytes)     │  │     (32 bytes)      │  │   (16 ports)     │   │ │
    │  │                     │  │                     │  │                     │  │                  │   │ │
    │  │ • Instructions      │  │ • Variables         │  │ • CALL/RET stack    │  │ • Input ports    │   │ │
    │  │ • Constants         │  │ • Temporary data    │  │ • PUSH/POP stack    │  │ • Output ports   │   │ │
    │  │ • Jump tables       │  │ • Arrays            │  │ • Descending        │  │ • Status regs    │   │ │
    │  └─────────────────────┘  └─────────────────────┘  └─────────────────────┘  └──────────────────┘   │ │
    │                                                                                                    │ │
    │  ┌────────────────────────────────────────────────────────────────────────────────────────────┐   │ │
    │  │                              MEMORY CONTROLLER                                            │   │ │
    │  │                                                                                            │   │ │
    │  │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  ┌─────────────────┐                │   │ │
    │  │  │   ADDRESS    │  │    DATA      │  │   CONTROL    │  │    ARBITRATOR   │                │   │ │
    │  │  │     BUS      │  │     BUS      │  │     BUS      │  │                 │                │   │ │
    │  │  │   (8-bit)    │  │   (8-bit)    │  │              │  │  • CPU access   │                │   │ │
    │  │  │              │  │              │  │  • READ_en   │  │  • DMA access   │                │   │ │
    │  │  │ 0x0000-0x02FF│  │ bidirectional│  │  • write_en  │  │  • I/O access   │                │   │ │
    │  │  └──────────────┘  └──────────────┘  └──────────────┘  └─────────────────┘                │   │ │
    │  └────────────────────────────────────────────────────────────────────────────────────────────┘   │ │
    └────────────────────────────────────────────────────────────────────────────────────────────────────┘ │
                                                                                                             │
    ┌────────────────────────────────────────────────────────────────────────────────────────────────────┐ │
    │                                     I/O SYSTEM                                                    │ │
    │                                                                                                    │ │
    │  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐           │ │
    │  │   INPUT PORTS    │  │  OUTPUT PORTS    │  │   STATUS PORTS   │  │   INTERRUPT      │           │ │
    │  │                  │  │                  │  │                  │  │   CONTROLLER     │           │ │
    │  │  PORT 0: KB_DATA │  │  PORT 8: DISP_D  │  │  PORT C: STATUS  │  │                  │           │ │
    │  │  PORT 1: KB_CTRL │  │  PORT 9: DISP_C  │  │  PORT D: ERROR   │  │  • IRQ handling  │           │ │
    │  │  PORT 2: SENSOR  │  │  PORT A: LED_OUT │  │  PORT E: DEBUG   │  │  • Vector table  │           │ │
    │  │  PORT 3: UART_RX │  │  PORT B: UART_TX │  │  PORT F: TIMER   │  │  • Priority      │           │ │
    │  └──────────────────┘  └──────────────────┘  └──────────────────┘  └──────────────────┘           │ │
    └────────────────────────────────────────────────────────────────────────────────────────────────────┘ │
                                                                                                             │
                                                     │                                                       │
                                                     │                                                       │
    ┌────────────────────────────────────────────────▼────────────────────────────────────────────────────┐ │
    │                                   EXTERNAL INTERFACES                                              │ │
    │                                                                                                    │ │
    │  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐           │ │
    │  │    KEYBOARD      │  │     DISPLAY      │  │       LED        │  │      UART        │           │ │
    │  │                  │  │                  │  │                  │  │                  │           │ │
    │  │  • 4x4 Matrix    │  │  • 7-segment     │  │  • Status LEDs   │  │  • Serial comm   │           │ │
    │  │  • Scan logic    │  │  • 2 digits      │  │  • Error LED     │  │  • 9600 baud     │           │ │
    │  │  • Debounce      │  │  • BCD decoder   │  │  • Power LED     │  │  • Debug output  │           │ │
    │  │  • ASCII conv    │  │  • Multiplexer   │  │  • Activity LED  │  │  • Programming   │           │ │
    │  └──────────────────┘  └──────────────────┘  └──────────────────┘  └──────────────────┘           │ │
    └────────────────────────────────────────────────────────────────────────────────────────────────────┘ │
                                                                                                             │
    ┌────────────────────────────────────────────────────────────────────────────────────────────────────┐ │
    │                                    CLOCK & RESET SYSTEM                                           │ │
    │                                                                                                    │ │
    │  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐           │ │
    │  │  CLOCK GENERATOR │  │  RESET CIRCUIT   │  │   POWER-ON-RST   │  │   WATCHDOG       │           │ │
    │  │                  │  │                  │  │                  │  │   TIMER          │           │ │
    │  │  • Crystal osc   │  │  • Manual reset  │  │  • POR circuit   │  │                  │           │ │
    │  │  • 8 MHz        │  │  • Button        │  │  • Delay circuit │  │  • Auto reset    │           │ │
    │  │  • Clock div     │  │  • Debounce      │  │  • Voltage mon   │  │  • Timeout det   │           │ │
    │  │  • Clock enable  │  │  • Active low    │  │  • Brown-out det │  │  • System health │           │ │
    │  └──────────────────┘  └──────────────────┘  └──────────────────┘  └──────────────────┘           │ │
    └────────────────────────────────────────────────────────────────────────────────────────────────────┘ │
                                                                                                             │
                                                     │                                                       │
                                          SISTEM COMPLET                                                    │
                                                     │                                                       │
                                                     ▼                                                       │
    ┌────────────────────────────────────────────────────────────────────────────────────────────────────┐ │
    │                                    SIGNAL CONNECTIONS                                             │ │
    │                                                                                                    │ │
    │  Clock Domain:                          Data Flow:                        Control Flow:           │ │
    │  • CLK → All sequential elements       • CPU ↔ Memory (8-bit data)      • Control Unit → ALU    │ │
    │  • RST → All reset inputs             • CPU ↔ I/O    (8-bit data)      • Control Unit → Regs   │ │
    │                                       • Stack ↔ SP   (address)         • Control Unit → Mem    │ │
    │  Address Flow:                         • PC → ROM     (address)         • Flags → Control Unit  │ │
    │  • PC → Program ROM                   • ALU → Flags  (status)          • External → I/O        │ │
    │  • SP → Stack RAM                                                                               │ │
    │  • Regs → Data RAM                    Timing:                                                    │ │
    │  • I/O addresses → Port decode        • Fetch: 1 cycle                                           │ │
    │                                       • Decode: 1 cycle                                          │ │
    │                                       • Execute: 1-3 cycles                                      │ │
    │                                       • Total: 3-5 cycles/instruction                            │ │
    └────────────────────────────────────────────────────────────────────────────────────────────────────┘ │
                                                                                                             │
                                                                                                             │
    ════════════════════════════════════════════════════════════════════════════════════════════════════════┘
```

## Specificații Tehnice Detaliate

### 1. CPU CORE - Specificații Complete

#### Registre (Register File)
```
Registru    | Dimensiune | Funcție                    | Resetare
-----------|-----------|----------------------------|----------
A (ACC)    | 8-bit     | Accumulator principal      | 0x00
B          | 8-bit     | Registru general          | 0x00
C          | 8-bit     | Registru general          | 0x00  
D          | 8-bit     | Registru general          | 0x00
X          | 8-bit     | Index register (optional)  | 0x00
Y          | 8-bit     | Index register (optional)  | 0x00
SP         | 8-bit     | Stack Pointer             | 0xFF
PC         | 8-bit     | Program Counter           | 0x00
FLAGS      | 4-bit     | Z,C,N,V flags             | 0x0
```

#### ALU - Operații Complete
```
OpCode | Operație | Descriere                    | Cycles | Flags
-------|----------|------------------------------|--------|-------
0000   | ADD      | A = A + B                   | 1      | Z,C,N,V
0001   | SUB      | A = A - B                   | 1      | Z,C,N,V
0010   | AND      | A = A & B                   | 1      | Z,N
0011   | OR       | A = A | B                   | 1      | Z,N
0100   | XOR      | A = A ^ B                   | 1      | Z,N
0101   | NOT      | A = ~A                      | 1      | Z,N
0110   | SHL      | A = A << 1                  | 1      | Z,C,N
0111   | SHR      | A = A >> 1                  | 1      | Z,C,N
1000   | INC      | A = A + 1                   | 1      | Z,C,N,V
1001   | DEC      | A = A - 1                   | 1      | Z,C,N,V
1010   | CMP      | Flags = A - B (no store)    | 1      | Z,C,N,V
1011   | Reserved | -                           | -      | -
1100   | MUL      | A = A * B (low 8-bit)       | 3      | Z,C,N
1101   | DIV      | A = A / B, B = A mod B      | 5      | Z,N
1110   | ROL      | A = rotate_left(A)          | 1      | Z,C,N
1111   | ROR      | A = rotate_right(A)         | 1      | Z,C,N
```

### 2. INSTRUCTION SET ARCHITECTURE (ISA)

#### Formatele de Instrucțiuni
```
Format 1: [OPCODE 4-bit][OPERAND 4-bit]       - Immediate/Register ops
Format 2: [OPCODE 4-bit][ADDRESS 4-bit]       - Memory operations  
Format 3: [OPCODE 8-bit]                      - No operand (NOP, HALT, RET)
```

#### Setul Complet de Instrucțiuni
```
Categorie        | Mnemonic | OpCode | Format | Descriere
-----------------|----------|--------|--------|---------------------------
Data Transfer    | LDA #n   | 0001   | 1      | A = immediate value
                 | LDA addr | 0010   | 2      | A = [memory address]
                 | LDB #n   | 0011   | 1      | B = immediate value  
                 | LDB addr | 0100   | 2      | B = [memory address]
                 | STA addr | 0101   | 2      | [memory address] = A
                 | STB addr | 0110   | 2      | [memory address] = B
                 | MOV B,A  | 0111   | 3      | B = A
                 |          |        |        |
Arithmetic       | ADD B    | 1000   | 3      | A = A + B
                 | SUB B    | 1001   | 3      | A = A - B
                 | INC A    | 1010   | 3      | A = A + 1
                 | DEC A    | 1011   | 3      | A = A - 1
                 | MUL B    | 1100   | 3      | A = A * B (8-bit result)
                 | DIV B    | 1101   | 3      | A = A/B, B = A mod B
                 |          |        |        |
Logic & Shift    | AND B    | 1110   | 3      | A = A & B
                 | OR B     | 1111   | 3      | A = A | B
                 | XOR B    | 0001   | 3      | A = A ^ B (next page)
                 | NOT A    | 0010   | 3      | A = ~A
                 | SHL A    | 0011   | 3      | A = A << 1
                 | SHR A    | 0100   | 3      | A = A >> 1
                 |          |        |        |
Control Flow     | JMP addr | 0101   | 2      | PC = address
                 | JZ addr  | 0110   | 2      | if Z=1 then PC = address
                 | JNZ addr | 0111   | 2      | if Z=0 then PC = address
                 | JC addr  | 1000   | 2      | if C=1 then PC = address
                 | JNC addr | 1001   | 2      | if C=0 then PC = address
                 | CMP B    | 1010   | 3      | Flags = A - B (no store)
                 |          |        |        |
Subroutines      | CALL addr| 1011   | 2      | Push PC; PC = address
                 | RET      | 1100   | 3      | PC = Pop from stack
                 | PUSH A   | 1101   | 3      | Push A to stack
                 | POP A    | 1110   | 3      | A = Pop from stack
                 |          |        |        |
System & I/O     | NOP      | 0000   | 3      | No operation
                 | HALT     | 1111   | 3      | Stop execution
                 | IN port  | 0001   | 1      | A = Input from port
                 | OUT port | 0010   | 1      | Output A to port
```

### 3. MEMORY MAPPING - Layout Detaliat

```
Address Range    | Size    | Type      | Usage
-----------------|---------|-----------|--------------------------------
0x0000 - 0x00FF  | 256 B   | ROM       | Program Memory
  0x0000         |         |           | • Reset vector
  0x0002         |         |           | • Interrupt vectors  
  0x0010         |         |           | • Program start
  0x00F0-0x00FF  |         |           | • Reserved for bootloader
                 |         |           |
0x0100 - 0x01DF  | 224 B   | RAM       | Data Memory  
  0x0100-0x011F  | 32 B    |           | • Global variables
  0x0120-0x017F  | 96 B    |           | • User data space
  0x0180-0x01DF  | 96 B    |           | • Temporary storage
                 |         |           |
0x01E0 - 0x01FF  | 32 B    | RAM       | Stack Memory
  0x01FF         |         |           | • Stack starts here (SP init)
  0x01E0         |         |           | • Stack overflow guard
                 |         |           |
0x0200 - 0x020F  | 16 B    | I/O       | Port Space
  0x0200-0x0207  | 8 ports |           | • Input ports
  0x0208-0x020F  | 8 ports |           | • Output ports
```

### 4. TIMING SPECIFICATIONS

#### Clock Specifications
```
Parameter           | Min  | Typical | Max  | Unit
-------------------|------|---------|------|-----
Clock Frequency    | 1    | 8       | 10   | MHz
Clock Period       | 100  | 125     | 1000 | ns
Clock Duty Cycle   | 45   | 50      | 55   | %
Clock Rise Time    | -    | 5       | 10   | ns
Clock Fall Time    | -    | 5       | 10   | ns
```

#### Instruction Timing
```
Instruction Type    | Cycles | Example Instructions
-------------------|--------|----------------------
Simple ALU         | 3      | ADD, SUB, AND, OR
Memory Load        | 4      | LDA addr, LDB addr  
Memory Store       | 4      | STA addr, STB addr
Branch (taken)     | 4      | JMP, JZ (when Z=1)
Branch (not taken) | 3      | JZ (when Z=0)
Call/Return        | 5      | CALL addr, RET
Stack Operations   | 4      | PUSH A, POP A
Complex ALU        | 8      | MUL B (multiply)
Division           | 12     | DIV B (divide)
I/O Operations     | 3      | IN port, OUT port
```

### 5. POWER AND RESET SPECIFICATIONS

#### Power Supply
```
Parameter           | Min  | Typical | Max  | Unit
-------------------|------|---------|------|-----
Supply Voltage     | 4.5  | 5.0     | 5.5  | V
Supply Current     | 50   | 100     | 150  | mA
Power Consumption  | 250  | 500     | 750  | mW
```

#### Reset Timing
```
Reset Type         | Duration | Description
-------------------|----------|---------------------------
Power-On Reset     | 100ms    | System startup reset
Manual Reset       | 10ms     | Button press reset
Watchdog Reset     | 1ms      | Automatic timeout reset
```

Această diagramă include:
1. **Toate componentele hardware** cu dimensiuni și conexiuni
2. **Fluxul de date** prin sistem  
3. **Controlul și semnalizarea** între module
4. **Specificații tehnice complete** pentru fiecare componentă
5. **Layout-ul memoriei** cu adrese exacte
6. **Timing-ul** instrucțiunilor și clock-ului

Poți folosi această diagramă pentru:
- **Implementarea în Verilog/VHDL**
- **Prezentarea arhitecturii** echipei
- **Ghid de design** pentru fiecare modul
- **Documentația tehnică** finală

Este destul de detaliată pentru a începe implementarea și suficient de clară pentru prezentare!