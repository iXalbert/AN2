# EasyEDA Setup Guide - Proiect Microsistem 8086

## 1. Pregătirea proiectului în EasyEDA

### Pasul 1: Crearea contului și proiectului
1. Accesează https://easyeda.com
2. Înregistrează-te sau loghează-te
3. Creează un nou proiect: "Microsistem_8086_[NumeStudent]"
4. Setează proprietățile proiectului:
   - Numele: Microsistem cu microprocesorul 8086
   - Descriere: Proiect pentru disciplina "Proiectarea cu Microprocesoare"

### Pasul 2: Structura schemelor
Organizează proiectul în următoarele scheme separate:

1. **Schema_Principala.sch** - Bloc diagrama generală
2. **CPU_si_Memorie.sch** - 8086 + memorii + decodificare
3. **Interfete_IO.sch** - 8251 + 8255 + microcomutatoare
4. **Perifericele.sch** - LED-uri + tastatură + afișaje

## 2. Lista componentelor pentru EasyEDA

### Microprocesoare și controlere
```
Componenta       Cantitate    Package    Descriere
-------------------------------------------------------
8086             1            DIP-40     Microprocesor principal
27C512           2            DIP-28     EPROM 64KB x 8
62256            2            DIP-28     SRAM 32KB x 8  
8251             1            DIP-28     Interfață serială USART
8255             1            DIP-40     Interfață paralelă PPI
```

### Logică și decodificare
```
74HC138          2            DIP-16     Decodor 3-la-8
74HC00           1            DIP-14     NAND gates
74HC04           1            DIP-14     NOT gates
74HC32           1            DIP-14     OR gates
74HC245          2            DIP-20     Buffer bidirecțional
74HC373          2            DIP-20     Latch transparent
```

### Oscilator și sincronizare
```
Crystal          1            HC-49      Cristal 8MHz
74HC04           1            DIP-14     Pentru oscilator
Condensatori     2            -          22pF pentru cristal
```

### Componente passive
```
Rezistențe       20           -          4.7kΩ (pull-up)
Rezistențe       10           -          330Ω (limitare LED)
Condensatori     10           -          100nF (decuplare)
Condensatori     4            -          10μF (filtrare)
```

### Perifericele
```
LED              10           -          LED roșii 3mm
Buton            9            -          Tactile switch
Afișaj 7-seg     8            -          Catod comun
LCD              1            -          2x16 caractere HD44780
Microcomutator   2            -          DIP switch 1 poziție
```

### Conectori
```
DB9 Female       1            -          Pentru interfață serială
Header 2x8       2            -          Pentru conexiuni
Header 1x16      1            -          Pentru LCD
```

## 3. Configurarea bibliotecilor EasyEDA

### Componente standard disponibile:
- 8086: Caută în biblioteca "Intel" sau "CPU"
- 74HC series: Biblioteca "74HC" sau "Logic"  
- LED, rezistențe: Biblioteca "Basic"

### Componente de creat manual:
Pentru componentele care nu există în bibliotecă, creează simboluri personalizate:

1. **8251 USART**
   - Creează simbol nou cu 28 de pini
   - Etichetează pinii conform datasheet-ului Intel

2. **8255 PPI** 
   - Creează simbol nou cu 40 de pini
   - Organizează pinii logic (PA0-7, PB0-7, PC0-7, control)

3. **Afișaj 7 segmente**
   - Creează simbol cu 10 pini (8 segmente + 2 comuni)
   - Adaugă etichete pentru segmentele a-g și punct

## 4. Convenții de desenare

### Denumirea semnalelor
```
Bus de adrese:    A0, A1, ..., A19
Bus de date:      D0, D1, ..., D15  
Control:          ALE, RD, WR, M_IO, DEN, DTR
Ceas:             CLK, RESET
Chip Select:      CS_ROM, CS_RAM, CS_8251, CS_8255
```

### Organizarea schemei
- Plasează CPU-ul în centru-stânga
- Memoriile în partea de sus
- I/O în partea de jos  
- Alimentarea în colțuri
- Folosește Net Labels pentru conexiuni între scheme

### Informații obligatorii pe schemă
În Title Block (zona info):
- Numele studentului
- Data creării/modificării
- Titlul schemei
- Numărul revizirii
- Universitatea și facultatea

## 5. Export și prezentare

### Pentru documentație:
1. Exportă schemele ca PDF (A4)
2. Asigură-te că toate textele sunt lizibile
3. Verifică că Title Block-ul este completat

### Pentru simulare:
1. Verifică toate conexiunile (ERC - Electrical Rules Check)
2. Adaugă test points unde este necesar
3. Documentează modificările în Change Log

## 6. Backup și versioning

- Salvează proiectul local periodic  
- Exportă toate schemele ca backup
- Folosește comentarii descriptive pentru modificări
- Creează snapshots înainte de modificări majore

## Următorii pași:
1. Creează proiectul în EasyEDA
2. Începe cu Schema_Principala.sch (bloc diagrama)
3. Continuă cu CPU_si_Memorie.sch (partea centrală)
4. Finalizează cu interfețele și perifericele