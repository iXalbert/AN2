# Specificații Hardware - Microsistem 8086

## 1. Componente principale

### Microprocesorul 8086
- Procesor pe 16 biți
- Bus de adrese: 20 biți (1MB spațiu adresabil)
- Bus de date: 16 biți
- Frecvența: 5-10 MHz
- Pinout: 40 pini (DIP)

### Memorii
#### EPROM - 27C512 (2 bucăți pentru 128KB)
- Capacitate: 64KB x 8 biți fiecare
- Organizare: 2 x 27C512 pentru bus de 16 biți
- Timp de acces: 250ns
- Tensiune: +5V
- Pinout: 28 pini

#### SRAM - 62256 (2 bucăți pentru 64KB)
- Capacitate: 32KB x 8 biți fiecare  
- Organizare: 2 x 62256 pentru bus de 16 biți
- Timp de acces: 150ns
- Tensiune: +5V
- Pinout: 28 pini

### Interfețe I/O

#### 8251 - Interfață serială (USART)
- Adrese: 04D0H-04D2H sau 05D0H-05D2H (controlat de S1)
- Registre: Data, Status, Control
- Viteze: 110 - 19200 baud
- Pinout: 28 pini

#### 8255 - Interfață paralelă (PPI)
- Adrese: 0250H-0256H sau 0A50H-0A56H (controlat de S2)
- 3 porturi x 8 biți (PA, PB, PC)
- Moduri: 0, 1, 2
- Pinout: 40 pini

## 2. Maparea memoriei

```
Adrese         Tip         Dimensiune    Componente
------------------------------------------------------
00000H-1FFFFH  EPROM       128KB         2 x 27C512
20000H-2FFFFH  SRAM        64KB          2 x 62256
30000H-FFFFFH  Liber       832KB         -
```

## 3. Maparea I/O

```
Adrese I/O     Dispozitiv       Funcție
--------------------------------------------
0250H-0256H    8255 (opțiunea 1)  Interfață paralelă
04D0H-04D2H    8251 (opțiunea 1)  Interfață serială
05D0H-05D2H    8251 (opțiunea 2)  Interfață serială  
0A50H-0A56H    8255 (opțiunea 2)  Interfață paralelă
```

## 4. Perifericele

### Minitastatură (9 contacte)
- Organizare: matrice 3x3
- Conectare: prin 8255 (Port A + Port C)
- Principiu: scanare pe linii, citire pe coloane

### LED-uri (10 bucăți)
- Conectare: prin 8255 (Port B + 2 biți Port C)
- Control: ieșire TTL cu rezistențe de limitare
- Curent: ~20mA per LED

### Afișaj 7 segmente (8 poziții)
- Tip: catod comun multiplexat
- Conectare: date prin 8255, control prin decodor
- Refresh rate: >50Hz pentru eliminarea pâlpâirii

### LCD 2x16
- Standard: HD44780 compatible
- Interfață: 4 sau 8 biți (la alegere)
- Conectare: prin 8255 sau direct la bus
- Alimentare: +5V

## 5. Semnale de control

### Microcomutatoare
- S1: selectează adresa 8251 (04D0H/05D0H)
- S2: selectează adresa 8255 (0250H/0A50H)

### Semnale bus 8086
- ALE (Address Latch Enable)
- RD (Read)
- WR (Write) 
- M/IO (Memory/IO select)
- DEN (Data Enable)
- DT/R (Data Transmit/Receive)

## 6. Considerații de design

### Decodificare adrese
- Folosirea unor gate-uri logice pentru selecția cipurilor
- Considerarea semnalelor M/IO pentru separarea spațiilor

### Sincronizare
- Wait states pentru memoriile lente
- Sincronizarea cu ceasul sistemului

### Alimentare
- +5V pentru toate componentele
- Filtrarea și stabilizarea tensiunii
- Considerarea curentului total consumat