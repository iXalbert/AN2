# FIC PROJECT - Scheme Logice pentru Instrucțiuni
## Procesorul General Purpose 16-bit

### Registre disponibile:
- **A** - Accumulator (16-bit)
- **X, Y** - Registre general purpose (16-bit)
- **FLAG** - Registru flag (4-bit): Zero, Negative, Carry, Overflow
- **SP** - Stack Pointer (16-bit)
- **PC** - Program Counter (16-bit)

---

## 1. INSTRUCȚIUNI DE MEMORIE (Load/Store)

### Format:
```
| Opcode | Register | Immediate |
|  6-bit |   1-bit  |   9-bit   |
```

### Registru Address Bit:
- **0** = X register
- **1** = Y register

### Instrucțiuni:

#### LOAD (LDR)
**Funcție:** Încarcă valoare din memorie în registru
```
Opcode: 000001
Format: LDR Reg, Address
Operație: Reg ← Memory[Address]
```

#### STORE (STR)
**Funcție:** Salvează valoare din registru în memorie
```
Opcode: 000010
Format: STR Reg, Address
Operație: Memory[Address] ← Reg
```

---

## 2. INSTRUCȚIUNI DE SALT (Branch)

### Format:
```
| Opcode | Address |
|  6-bit | 10-bit  |
```

### Instrucțiuni:

#### BRZ - Branch if Zero
```
Opcode: 100001
Condiție: FLAG.Zero = 1
Operație: if (Zero) then PC ← Address
```

#### BRN - Branch if Negative
```
Opcode: 100010
Condiție: FLAG.Negative = 1
Operație: if (Negative) then PC ← Address
```

#### BRC - Branch if Carry
```
Opcode: 100011
Condiție: FLAG.Carry = 1
Operație: if (Carry) then PC ← Address
```

#### BRO - Branch if Overflow
```
Opcode: 100100
Condiție: FLAG.Overflow = 1
Operație: if (Overflow) then PC ← Address
```

#### BRA - Branch Always
```
Opcode: 100101
Condiție: Întotdeauna
Operație: PC ← Address
```

#### JMP - Call Procedure
```
Opcode: 100110
Operație: 
1. Stack[SP] ← PC
2. SP ← SP - 1
3. PC ← Address
```

#### RET - Return from Procedure
```
Opcode: 100111
Operație:
1. SP ← SP + 1
2. PC ← Stack[SP]
```

---

## 3. INSTRUCȚIUNI ARITMETICE ȘI LOGICE

### Format:
```
| Opcode | Register | Immediate |
|  6-bit |   1-bit  |   9-bit   |
```

**Notă:** Toate aceste instrucțiuni actualizează registrul FLAG!

### Instrucțiuni Aritmetice:

#### ADD - Adunare
```
Opcode: 010001
Format: ADD Reg
Operație: A ← A + Reg
Flag Update: Zero, Negative, Carry, Overflow
```

#### SUB - Scădere
```
Opcode: 010010
Format: SUB Reg
Operație: A ← A - Reg
Flag Update: Zero, Negative, Carry, Overflow
```

#### MUL - Înmulțire
```
Opcode: 010011
Format: MUL Reg
Operație: A ← A * Reg
Flag Update: Zero, Negative, Carry, Overflow
```

#### DIV - Împărțire
```
Opcode: 010100
Format: DIV Reg
Operație: A ← A / Reg
Flag Update: Zero, Negative
```

#### MOD - Modulo
```
Opcode: 010101
Format: MOD Reg
Operație: A ← A % Reg
Flag Update: Zero, Negative
```

#### INC - Incrementare
```
Opcode: 010110
Format: INC Reg
Operație: Reg ← Reg + 1
Flag Update: Zero, Negative, Carry, Overflow
```

#### DEC - Decrementare
```
Opcode: 010111
Format: DEC Reg
Operație: Reg ← Reg - 1
Flag Update: Zero, Negative, Carry, Overflow
```

### Instrucțiuni de Shift:

#### LSL - Logic Shift Left
```
Opcode: 011001
Format: LSL Reg
Operație: A ← A << 1
Flag Update: Zero, Negative, Carry
```

#### LSR - Logic Shift Right
```
Opcode: 011010
Format: LSR Reg
Operație: A ← A >> 1
Flag Update: Zero, Negative, Carry
```

#### RSL - Rotate Shift Left
```
Opcode: 011011
Format: RSL Reg
Operație: A ← rotate_left(A, 1)
Flag Update: Zero, Negative, Carry
```

#### RSR - Rotate Shift Right
```
Opcode: 011100
Format: RSR Reg
Operație: A ← rotate_right(A, 1)
Flag Update: Zero, Negative, Carry
```

### Instrucțiuni Logice:

#### AND - Logic AND
```
Opcode: 001001
Format: AND Reg
Operație: A ← A & Reg
Flag Update: Zero, Negative
```

#### OR - Logic OR
```
Opcode: 001010
Format: OR Reg
Operație: A ← A | Reg
Flag Update: Zero, Negative
```

#### XOR - Logic XOR
```
Opcode: 001011
Format: XOR Reg
Operație: A ← A ⊕ Reg
Flag Update: Zero, Negative
```

#### NOT - Logic NOT
```
Opcode: 001100
Format: NOT Reg
Operație: A ← ~Reg
Flag Update: Zero, Negative
```

### Instrucțiuni de Comparare:

#### CMP - Compare
```
Opcode: 001101
Format: CMP Reg
Operație: temp ← A - Reg (nu salvează rezultatul)
Flag Update: Zero, Negative, Carry, Overflow
```

#### TST - Test
```
Opcode: 001110
Format: TST Reg
Operație: temp ← A & Reg (nu salvează rezultatul)
Flag Update: Zero, Negative
```

### Instrucțiuni de Transfer:

#### MOV - Move
```
Opcode: 001111
Format: MOV Reg
Operație: A ← Reg
Flag Update: Zero, Negative
```

---

## 4. ACTUALIZAREA FLAG-URILOR

### Flag Register (4-bit):
```
| Bit 3 | Bit 2 | Bit 1 | Bit 0 |
| Zero  | Negative | Carry | Overflow |
```

### Reguli de actualizare:

#### Zero Flag (Z):
- Se setează la 1 dacă rezultatul operației este 0
- Se setează la 0 dacă rezultatul operației este diferit de 0

#### Negative Flag (N):
- Se setează la 1 dacă bitul de semn (bit 15) al rezultatului este 1
- Se setează la 0 dacă bitul de semn al rezultatului este 0

#### Carry Flag (C):
- Pentru adunare: se setează la 1 dacă există transport din bitul 15
- Pentru scădere: se setează la 1 dacă există împrumut
- Pentru shift: se setează la valoarea bitului care "iese"

#### Overflow Flag (V):
- Se setează la 1 dacă operația cauzează overflow în complement de 2
- Pentru adunare: (A[15] = B[15]) AND (Result[15] ≠ A[15])
- Pentru scădere: (A[15] ≠ B[15]) AND (Result[15] ≠ A[15])

---

## 5. EXEMPLE DE UTILIZARE

### Exemplu 1: Încărcare și adunare
```assembly
LDR X, 0x100    ; Încarcă valoarea de la adresa 0x100 în X
LDR Y, 0x101    ; Încarcă valoarea de la adresa 0x101 în Y
MOV X           ; Mută X în A
ADD Y           ; Adună Y la A, rezultatul în A
STR A, 0x102    ; Salvează rezultatul la adresa 0x102
```

### Exemplu 2: Bucla cu condiție
```assembly
LDR X, 0x200    ; Încarcă counter-ul
loop:
    DEC X       ; Decrementează X
    TST X       ; Testează X
    BRZ end     ; Sari la end dacă X = 0
    BRA loop    ; Altfel, continuă bucla
end:
    RET         ; Return
```

### Exemplu 3: Apel de procedură
```assembly
LDR X, 0x300    ; Pregătește parametrul
JMP procedure   ; Apelează procedura
STR A, 0x301    ; Salvează rezultatul

procedure:
    ADD X       ; Operația dorită
    RET         ; Return cu rezultatul în A
```

---

## 6. COMPONENTE CPU MINIME NECESARE

### Registre:
- A (Accumulator) - 16-bit
- X, Y (General Purpose) - 16-bit fiecare
- PC (Program Counter) - 16-bit
- SP (Stack Pointer) - 16-bit
- FLAG - 4-bit

### Unități functionale:
- **ALU** - pentru operațiile aritmetice și logice
- **Control Unit** - pentru decodificarea și execuția instrucțiunilor
- **Sign Extend Unit** - pentru extinderea valorilor immediate
- **Memory Unit** - pentru accesul la memorie (instrucțiuni și date)

### Căi de date:
- Bus intern 16-bit pentru transferul datelor
- Multiplexoare pentru selectarea surselor
- Buffer-e pentru ieșirile ALU

---

## 7. NOTIȚE IMPORTANTE

1. **Stack-ul crește invers în memorie** (SP scade la push)
2. **Doar instrucțiunile aritmetice și logice actualizează FLAG-ul**
3. **Parametrii procedurilor se trec prin stack**
4. **Valoarea de return se trece prin stack**
5. **Immediate-ul este de 9-bit, deci valorile sunt [-256, 255]**
6. **Adresele pentru branch sunt de 10-bit, deci [0, 1023]**

---

*Documentul creat pentru proiectul FIC - Procesorul General Purpose 16-bit*
*Echipa: [Nume echipă]*
*Data: $(date +%Y-%m-%d)*