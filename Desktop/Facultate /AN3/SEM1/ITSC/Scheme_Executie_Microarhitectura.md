# SCHEME DE EXECUȚIE MICROARHITECTURALĂ
## Procesorul General Purpose 16-bit

### Convenții:
- **IR** - Instruction Register (conține instrucțiunea curentă)
- **AR** - Address Register (conține adresa curentă)
- **DR** - Data Register (conține date temporare)
- **TR** - Temporary Register (registru temporar pentru ALU)
- **MEM** - Memoria
- **PC** - Program Counter
- **SP** - Stack Pointer
- **A, X, Y** - Registre generale
- **FLAG** - Registrul de flag-uri

---

## CICLU FETCH (comun pentru toate instrucțiunile)

```
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare instrucțiune
```

---

## 1. INSTRUCȚIUNI DE MEMORIE

### LDR Reg, Address (Load Register)
**Opcode: 000001**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 000001)

Ciclu EXECUTE:
T3: AR ← IR[Address]              // Extrage adresa din IR (biți 0-8)
T4: DR ← MEM[AR]                  // Citește din memorie
T5: if (IR[Reg_bit] = 0)          // Verifică bit 9
        X ← DR
    else
        Y ← DR
```

---

### STR Reg, Address (Store Register)
**Opcode: 000010**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 000010)

Ciclu EXECUTE:
T3: AR ← IR[Address]              // Extrage adresa din IR (biți 0-8)
T4: if (IR[Reg_bit] = 0)          // Verifică bit 9
        DR ← X
    else
        DR ← Y
T5: MEM[AR] ← DR                  // Scrie în memorie
```

---

## 2. INSTRUCȚIUNI DE SALT (BRANCH)

### BRZ Address (Branch if Zero)
**Opcode: 100001**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 100001)

Ciclu EXECUTE:
T3: if (FLAG[3] = 1)              // Verifică Zero flag
        PC ← IR[Address]          // Sare la adresă (biți 0-9)
```

---

### BRN Address (Branch if Negative)
**Opcode: 100010**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 100010)

Ciclu EXECUTE:
T3: if (FLAG[2] = 1)              // Verifică Negative flag
        PC ← IR[Address]
```

---

### BRC Address (Branch if Carry)
**Opcode: 100011**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 100011)

Ciclu EXECUTE:
T3: if (FLAG[1] = 1)              // Verifică Carry flag
        PC ← IR[Address]
```

---

### BRO Address (Branch if Overflow)
**Opcode: 100100**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 100100)

Ciclu EXECUTE:
T3: if (FLAG[0] = 1)              // Verifică Overflow flag
        PC ← IR[Address]
```

---

### BRA Address (Branch Always)
**Opcode: 100101**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 100101)

Ciclu EXECUTE:
T3: PC ← IR[Address]              // Sare necondiționat
```

---

### JMP Address (Call Procedure)
**Opcode: 100110**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 100110)

Ciclu EXECUTE:
T3: AR ← SP                       // Pregătește adresa stack
T4: DR ← PC                       // Salvează PC curent
T5: MEM[AR] ← DR                  // Push PC pe stack
T6: SP ← SP - 1                   // Decrementează stack pointer
T7: PC ← IR[Address]              // Sare la procedură
```

---

### RET (Return from Procedure)
**Opcode: 100111**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 100111)

Ciclu EXECUTE:
T3: SP ← SP + 1                   // Incrementează stack pointer
T4: AR ← SP                       // Pregătește adresa stack
T5: DR ← MEM[AR]                  // Pop PC de pe stack
T6: PC ← DR                       // Restaurează PC
```

---

## 3. INSTRUCȚIUNI ARITMETICE

### ADD Reg (Addition)
**Opcode: 010001**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 010001)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)          // Selectează registrul
        TR ← X
    else
        TR ← Y
T4: A ← A + TR                    // Operație ALU
T5: Actualizează FLAG (Z, N, C, V)
```

---

### SUB Reg (Subtraction)
**Opcode: 010010**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 010010)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: A ← A - TR                    // Operație ALU
T5: Actualizează FLAG (Z, N, C, V)
```

---

### MUL Reg (Multiplication)
**Opcode: 010011**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 010011)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: A ← A * TR                    // Operație ALU (înmulțire)
T5: Actualizează FLAG (Z, N, C, V)
```

---

### DIV Reg (Division)
**Opcode: 010100**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 010100)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: A ← A / TR                    // Operație ALU (împărțire)
T5: Actualizează FLAG (Z, N)
```

---

### MOD Reg (Modulo)
**Opcode: 010101**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 010101)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: A ← A % TR                    // Operație ALU (modulo)
T5: Actualizează FLAG (Z, N)
```

---

### INC Reg (Increment)
**Opcode: 010110**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 010110)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        X ← X + 1                 // Incrementează X
    else
        Y ← Y + 1                 // Incrementează Y
T4: Actualizează FLAG (Z, N, C, V)
```

---

### DEC Reg (Decrement)
**Opcode: 010111**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 010111)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        X ← X - 1                 // Decrementează X
    else
        Y ← Y - 1                 // Decrementează Y
T4: Actualizează FLAG (Z, N, C, V)
```

---

## 4. INSTRUCȚIUNI DE SHIFT

### LSL Reg (Logic Shift Left)
**Opcode: 011001**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 011001)

Ciclu EXECUTE:
T3: TR ← A                        // Copie temporară
T4: A ← A << 1                    // Shift la stânga logic
T5: FLAG[1] ← TR[15]              // Carry = bitul care iese
T6: Actualizează FLAG (Z, N, C)
```

---

### LSR Reg (Logic Shift Right)
**Opcode: 011010**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 011010)

Ciclu EXECUTE:
T3: TR ← A                        // Copie temporară
T4: A ← A >> 1                    // Shift la dreapta logic
T5: FLAG[1] ← TR[0]               // Carry = bitul care iese
T6: Actualizează FLAG (Z, N, C)
```

---

### RSL Reg (Rotate Shift Left)
**Opcode: 011011**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 011011)

Ciclu EXECUTE:
T3: TR ← A[15]                    // Salvează bitul MSB
T4: A ← (A << 1) | TR             // Rotație la stânga
T5: FLAG[1] ← TR                  // Carry = bitul rotit
T6: Actualizează FLAG (Z, N, C)
```

---

### RSR Reg (Rotate Shift Right)
**Opcode: 011100**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 011100)

Ciclu EXECUTE:
T3: TR ← A[0]                     // Salvează bitul LSB
T4: A ← (A >> 1) | (TR << 15)    // Rotație la dreapta
T5: FLAG[1] ← TR                  // Carry = bitul rotit
T6: Actualizează FLAG (Z, N, C)
```

---

## 5. INSTRUCȚIUNI LOGICE

### AND Reg (Logic AND)
**Opcode: 001001**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 001001)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: A ← A & TR                    // Operație AND
T5: Actualizează FLAG (Z, N)
```

---

### OR Reg (Logic OR)
**Opcode: 001010**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 001010)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: A ← A | TR                    // Operație OR
T5: Actualizează FLAG (Z, N)
```

---

### XOR Reg (Logic XOR)
**Opcode: 001011**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 001011)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: A ← A ⊕ TR                    // Operație XOR
T5: Actualizează FLAG (Z, N)
```

---

### NOT Reg (Logic NOT)
**Opcode: 001100**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 001100)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: A ← ~TR                       // Operație NOT
T5: Actualizează FLAG (Z, N)
```

---

## 6. INSTRUCȚIUNI DE COMPARARE

### CMP Reg (Compare)
**Opcode: 001101**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 001101)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: DR ← A - TR                   // Scădere fără salvare
T5: Actualizează FLAG (Z, N, C, V) bazat pe DR
    // A rămâne neschimbat!
```

---

### TST Reg (Test)
**Opcode: 001110**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 001110)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        TR ← X
    else
        TR ← Y
T4: DR ← A & TR                   // AND fără salvare
T5: Actualizează FLAG (Z, N) bazat pe DR
    // A rămâne neschimbat!
```

---

## 7. INSTRUCȚIUNI DE TRANSFER

### MOV Reg (Move)
**Opcode: 001111**

```
Ciclu FETCH:
T0: AR ← PC
T1: IR ← MEM[AR], PC ← PC + 1
T2: Decodificare (Opcode = 001111)

Ciclu EXECUTE:
T3: if (IR[Reg_bit] = 0)
        A ← X                     // Transfer din X în A
    else
        A ← Y                     // Transfer din Y în A
T4: Actualizează FLAG (Z, N)
```

---

## 8. DETALII ACTUALIZARE FLAG

### Logica de actualizare FLAG:

```
Zero Flag (FLAG[3]):
    if (Rezultat = 0)
        FLAG[3] ← 1
    else
        FLAG[3] ← 0

Negative Flag (FLAG[2]):
    FLAG[2] ← Rezultat[15]        // Bitul de semn

Carry Flag (FLAG[1]):
    // Pentru adunare
    if (A[15] + B[15] > 15 biți)
        FLAG[1] ← 1
    // Pentru scădere
    if (A < B)                    // Împrumut
        FLAG[1] ← 1
    // Pentru shift
    FLAG[1] ← bit care iese

Overflow Flag (FLAG[0]):
    // Pentru adunare
    if (A[15] = B[15]) AND (Rezultat[15] ≠ A[15])
        FLAG[0] ← 1
    // Pentru scădere
    if (A[15] ≠ B[15]) AND (Rezultat[15] ≠ A[15])
        FLAG[0] ← 1
```

---

## 9. REGISTRE MICROARHITECTURALE NECESARE

```
Registre vizibile programatorului:
- A (16-bit)     : Accumulator
- X (16-bit)     : General purpose
- Y (16-bit)     : General purpose
- PC (16-bit)    : Program Counter
- SP (16-bit)    : Stack Pointer
- FLAG (4-bit)   : Z, N, C, V

Registre interne (microarhitectură):
- IR (16-bit)    : Instruction Register
- AR (16-bit)    : Address Register
- DR (16-bit)    : Data Register
- TR (16-bit)    : Temporary Register (pentru ALU)
```

---

## 10. TABLĂ REZUMATIVĂ - MICROOPERAȚII

| Instrucțiune | T3 | T4 | T5 | T6 | T7 |
|--------------|----|----|----|----|-----|
| **LDR** | AR←IR[Addr] | DR←MEM[AR] | Reg←DR | - | - |
| **STR** | AR←IR[Addr] | DR←Reg | MEM[AR]←DR | - | - |
| **BRZ** | if Z: PC←IR[Addr] | - | - | - | - |
| **BRN** | if N: PC←IR[Addr] | - | - | - | - |
| **BRC** | if C: PC←IR[Addr] | - | - | - | - |
| **BRO** | if V: PC←IR[Addr] | - | - | - | - |
| **BRA** | PC←IR[Addr] | - | - | - | - |
| **JMP** | AR←SP | DR←PC | MEM[AR]←DR | SP←SP-1 | PC←IR[Addr] |
| **RET** | SP←SP+1 | AR←SP | DR←MEM[AR] | PC←DR | - |
| **ADD** | TR←Reg | A←A+TR | Update FLAG | - | - |
| **SUB** | TR←Reg | A←A-TR | Update FLAG | - | - |
| **MUL** | TR←Reg | A←A*TR | Update FLAG | - | - |
| **DIV** | TR←Reg | A←A/TR | Update FLAG | - | - |
| **MOD** | TR←Reg | A←A%TR | Update FLAG | - | - |
| **INC** | Reg←Reg+1 | Update FLAG | - | - | - |
| **DEC** | Reg←Reg-1 | Update FLAG | - | - | - |
| **LSL** | TR←A | A←A<<1 | C←TR[15] | Update FLAG | - |
| **LSR** | TR←A | A←A>>1 | C←TR[0] | Update FLAG | - |
| **RSL** | TR←A[15] | A←(A<<1)|TR | C←TR | Update FLAG | - |
| **RSR** | TR←A[0] | A←(A>>1)|(TR<<15) | C←TR | Update FLAG | - |
| **AND** | TR←Reg | A←A&TR | Update FLAG | - | - |
| **OR** | TR←Reg | A←A|TR | Update FLAG | - | - |
| **XOR** | TR←Reg | A←A⊕TR | Update FLAG | - | - |
| **NOT** | TR←Reg | A←~TR | Update FLAG | - | - |
| **CMP** | TR←Reg | DR←A-TR | Update FLAG | - | - |
| **TST** | TR←Reg | DR←A&TR | Update FLAG | - | - |
| **MOV** | A←Reg | Update FLAG | - | - | - |

---

**Notă:** Toate instrucțiunile au ciclul FETCH standard (T0-T2) înainte de ciclul EXECUTE.

---

*Document generat pentru proiectul FIC - Procesorul General Purpose 16-bit*
*Scheme de execuție la nivel microarhitectural*
