# UNIVERSITATEA TEHNICĂ DIN CLUJ-NAPOCA
## FACULTATEA DE AUTOMATICĂ ȘI CALCULATOARE
### PROIECTAREA CU MICROPROCESOARE

**MICROSISTEM CU MICROPROCESORUL 8086**

**Student:** Albert Rosca  
**Anul universitar:** 2025-2026

---

## TEMA PROIECTULUI

Să se proiecteze un microsistem cu următoarea structură:
- unitate centrală cu microprocesorul 8086
- 128 KB memorie EPROM, utilizând circuite 27C512
- 64 KB memorie SRAM, utilizând circuite 62256
- interfață serială, cu circuitul 8251, plasată în zona 04D0H – 04D2H sau 05D0H – 05D2H, în funcție de poziția microcomutatorului S1
- interfață paralelă, cu circuitul 8255, plasată în zona 0250H– 0256H sau 0A50H – 0A56H, în funcție de poziția microcomutatorului S2
- o minitastatură cu 9 contacte
- 10 led-uri
- un modul de afișare cu 7 segmente, cu 8 ranguri (se pot afișa maxim 8 caractere hexa simultan)
- un modul LCD, cu 2 linii a câte 16 caractere fiecare, cu o interfață la alegerea studentului

---

## DESCRIEREA HARDWARE-ULUI

### 1. Arhitectura generală a sistemului
[Descriere bloc-diagramă generală]

### 2. Unitatea centrală - Microprocesorul 8086
[Caracteristici și funcționare]

### 3. Subsistemul de memorie
#### 3.1 Memoria EPROM (128 KB - 27C512)
[Organizare și mapare în spațiul de adrese]

#### 3.2 Memoria SRAM (64 KB - 62256) 
[Organizare și mapare în spațiul de adrese]

#### 3.3 Decodificarea adreselor
[Schema și logica de decodificare]

### 4. Interfețele de intrare/ieșire
#### 4.1 Interfața serială (8251)
[Configurare și adresare variabilă cu S1]

#### 4.2 Interfața paralelă (8255)
[Configurare și adresare variabilă cu S2]

### 5. Perifericele
#### 5.1 Minitastatura (9 contacte)
[Schema de conectare și principiul de scanare]

#### 5.2 LED-urile (10 bucăți)
[Schema de conectare și control]

#### 5.3 Afișajul cu 7 segmente (8 ranguri)
[Schema de conectare și multiplexare]

#### 5.4 Modulul LCD (2x16 caractere)
[Interfață și protocolul de comunicare]

---

## PROGRAMELE ÎN LIMBAJ DE ASAMBLARE

### 1. Rutinele de programare
#### 1.1 Rutina de programare a circuitului 8251
```assembly
; Rutină de inițializare 8251
; Intrări: 
; Ieșiri:
; Registre modificate:
```

#### 1.2 Rutina de programare a circuitului 8255
```assembly
; Rutină de inițializare 8255
; Intrări: 
; Ieșiri:
; Registre modificate:
```

### 2. Rutinele de comunicare serială
#### 2.1 Rutina de emisie caracter pe interfața serială
```assembly
; Rutină de transmisie serială
; Intrări: AL = caracterul de transmis
; Ieșiri: 
; Registre modificate:
```

#### 2.2 Rutina de recepție caracter pe interfața serială
```assembly
; Rutină de recepție serială
; Intrări: 
; Ieșiri: AL = caracterul recepționat
; Registre modificate:
```

### 3. Rutina de emisie caracter pe interfața paralelă
```assembly
; Rutină de transmisie paralelă
; Intrări: AL = caracterul de transmis
; Ieșiri: 
; Registre modificate:
```

### 4. Rutina de scanare a minitastaturii
```assembly
; Rutină de scanare tastatură
; Intrări: 
; Ieșiri: AL = codul tastei apăsate
; Registre modificate:
```

### 5. Rutina de control LED-uri
```assembly
; Rutină aprindere/stingere LED
; Intrări: AL = masca LED-urilor
; Ieșiri: 
; Registre modificate:
```

### 6. Rutina de afișare pe 7 segmente
```assembly
; Rutină afișare caracter hexa pe 7 segmente
; Intrări: AL = caracterul hexa, BL = rangul
; Ieșiri: 
; Registre modificate:
```

---

## BIBLIOGRAFIA

[1] Mircea Popa, "Sisteme cu microprocesoare", Editura Orizonturi Universitare, 2000.

[2] Intel Corporation, "8086/8088 User's Manual - Programmer's and Hardware Reference", Intel, 1981.

[3] Intel Corporation, "8251A Programmable Communication Interface", Intel Data Sheet, 1979.

[4] Intel Corporation, "8255A Programmable Peripheral Interface", Intel Data Sheet, 1977.

[5] EasyEDA Online Circuit Design Platform, https://easyeda.com (accesat în noiembrie 2025).

---

**Notă:** Acest template trebuie completat cu informațiile specifice proiectului realizat.