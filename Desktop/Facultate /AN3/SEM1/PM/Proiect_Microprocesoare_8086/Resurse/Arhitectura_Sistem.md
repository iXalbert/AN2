# Arhitectura Microsistemului cu 8086

## 1. Diagrama bloc generală

```
                    ┌─────────────────────────────────────────────────┐
                    │                MICROSISTEM 8086                │
                    └─────────────────────────────────────────────────┘
                                           │
            ┌─────────────┬─────────────────┼─────────────────┬─────────────┐
            │             │                 │                 │             │
         ┌──▼──┐      ┌───▼────┐       ┌────▼─────┐      ┌───▼────┐    ┌───▼───┐
         │ CPU │      │MEMORIA │       │DECODIFICARE│      │ I/O    │    │PERIFERICE│
         │8086 │      │SUBSYS  │       │ ADRESE   │      │INTERFACES│    │      │
         └─────┘      └────────┘       └──────────┘      └────────┘    └───────┘
```

## 2. Arhitectura detaliată

### 2.1 Unitatea Centrală (CPU 8086)

```
                        8086 MICROPROCESSOR
    ┌─────────────────────────────────────────────────────┐
    │  AD0-AD15   │  A16-A19  │ ALE │ RD │ WR │ M/IO │ DEN │
    └──────┬──────┴─────┬─────┴─────┴────┴────┴──────┴─────┘
           │            │
           │            └─── Address Bus (A0-A19) ───────────┐
           └─── Address/Data Bus (AD0-AD15) ─────────────────┤
                                                             │
    ┌─────────────────────────────────────────────────────────────┐
    │                BUS CONTROLLER                               │
    │  ┌──────────┐  ┌─────────┐  ┌──────────┐  ┌──────────┐   │
    │  │74HC373   │  │74HC245  │  │ Address  │  │ Control  │   │
    │  │Address   │  │Data     │  │ Decoder  │  │ Logic    │   │
    │  │Latch     │  │Buffer   │  │          │  │          │   │
    │  └──────────┘  └─────────┘  └──────────┘  └──────────┘   │
    └─────────────────────────────────────────────────────────────┘
```

### 2.2 Subsistemul de memorie

```
                        MEMORY SUBSYSTEM
    
    A0-A19 ──────┬─────────────────┬─────────────────┐
                 │                 │                 │
        ┌────────▼─────────┐  ┌────▼────┐  ┌────────▼─────────┐
        │   EPROM BANK     │  │ADDRESS  │  │   SRAM BANK      │
        │                  │  │DECODER  │  │                  │
        │ ┌─────┬─────┐   │  │         │  │ ┌─────┬─────┐   │
        │ │27C512│27C512│  │  │74HC138  │  │ │62256│62256│   │
        │ │LOW  │HIGH │   │  │         │  │ │LOW  │HIGH │   │
        │ │BYTE │BYTE │   │  │         │  │ │BYTE │BYTE │   │
        │ └─────┴─────┘   │  └─────────┘  │ └─────┴─────┘   │
        │   128KB EPROM    │               │   64KB SRAM      │
        │ 00000H-1FFFFH   │               │ 20000H-2FFFFH   │
        └──────────────────┘               └──────────────────┘
                 │                                   │
                 └───────────── D0-D15 ──────────────┘
```

### 2.3 Maparea memoriei detaliată

```
      MEMORY MAP
    ┌─────────────┬──────────────┬─────────────────┬─────────────┐
    │   Adrese    │    Tip       │   Componente    │  Dimensiune │
    ├─────────────┼──────────────┼─────────────────┼─────────────┤
    │00000-1FFFF  │   EPROM      │ 2 x 27C512     │   128KB     │
    │20000-2FFFF  │   SRAM       │ 2 x 62256      │    64KB     │  
    │30000-EFFFF  │   REZERVAT   │      -          │   768KB     │
    │F0000-FFFFF  │   BIOS       │ (opțional)      │    64KB     │
    └─────────────┴──────────────┴─────────────────┴─────────────┘

    Decodificare EPROM: A19=0, A18=0, A17=0,1 (000x xxxx xxxx xxxx xxxx)  
    Decodificare SRAM:  A19=0, A18=0, A17=1,0 (001x xxxx xxxx xxxx xxxx)
```

### 2.4 Sistemul de I/O

```
                           I/O SUBSYSTEM
    
    A0-A15 ──────┬─────────────────┬─────────────────┐
                 │                 │                 │
        ┌────────▼─────────┐  ┌────▼────┐  ┌────────▼─────────┐
        │  SERIAL I/F      │  │ I/O     │  │  PARALLEL I/F    │
        │     8251         │  │DECODER  │  │     8255         │
        │                  │  │         │  │                  │
        │ Port: 04D0H-04D2H│  │   S1    │  │Port: 0250H-0256H │
        │    or 05D0H-05D2H│  │   S2    │  │   or 0A50H-0A56H │
        │                  │  │         │  │                  │
        │ ┌──────────────┐ │  └─────────┘  │┌─────┬─────┬────┐│
        │ │   DATA REG   │ │               ││PORT │PORT │PORT││
        │ │  STATUS REG  │ │               ││  A  │  B  │ C  ││
        │ │ CONTROL REG  │ │               ││ 8bit│ 8bit│8bit││
        │ └──────────────┘ │               │└─────┴─────┴────┘│
        └──────────────────┘               └──────────────────┘
                 │                                   │
                 │                                   │
         ┌───────▼────────┐                 ┌────────▼─────────┐
         │   DB9 CONN     │                 │   PERIPHERALS    │
         │   SERIAL       │                 │  KEYBOARD, LEDS  │
         │   RS232        │                 │   7-SEG, LCD     │
         └────────────────┘                 └──────────────────┘
```

### 2.5 Interfețele cu adresare configurabilă

```
                    SWITCHABLE ADDRESSING
    
    Microcomutator S1 (pentru 8251):
    ┌─────┬──────────────┬─────────────────────┐
    │ S1  │   Adrese     │      Funcție        │
    ├─────┼──────────────┼─────────────────────┤
    │  0  │ 04D0H-04D2H  │ Data/Status/Control │
    │  1  │ 05D0H-05D2H  │ Data/Status/Control │
    └─────┴──────────────┴─────────────────────┘
    
    Microcomutator S2 (pentru 8255):
    ┌─────┬──────────────┬─────────────────────┐
    │ S2  │   Adrese     │      Funcție        │
    ├─────┼──────────────┼─────────────────────┤
    │  0  │ 0250H-0256H  │ PortA/B/C/Control   │
    │  1  │ 0A50H-0A56H  │ PortA/B/C/Control   │
    └─────┴──────────────┴─────────────────────┘
```

### 2.6 Perifericele conectate prin 8255

```
                        PERIPHERAL CONNECTIONS
    
                    8255 PROGRAMMABLE PERIPHERAL INTERFACE
    ┌─────────────────────────────────────────────────────────────┐
    │                                                             │
    │  PORT A (PA0-PA7)          PORT B (PB0-PB7)    PORT C      │
    │  ┌─────────────────┐      ┌─────────────────┐  ┌────────┐   │
    │  │  KEYBOARD       │      │   10 LEDs       │  │CONTROL │   │
    │  │  SCAN MATRIX    │      │   PB0-PB7 = 8   │  │ 7-SEG  │   │
    │  │     3x3         │      │   PC0-PC1 = 2   │  │DISPLAY │   │
    │  │                 │      │                 │  │        │   │
    │  │ PA0-PA2: Rows   │      │ R=330Ω each     │  │PC2-PC5 │   │
    │  │ PA3-PA5: Cols   │      │                 │  │        │   │
    │  └─────────────────┘      └─────────────────┘  └────────┘   │
    └─────────────────────────────────────────────────────────────┘
                         │                 │              │
                         │                 │              │
                ┌────────▼──────┐  ┌───────▼──────┐  ┌───▼─────────┐
                │  9 SWITCHES   │  │  10 LEDs     │  │8x7-SEGMENT  │
                │   MATRIX      │  │   STATUS     │  │  DISPLAY    │
                │               │  │   OUTPUT     │  │  (MUX)      │
                └───────────────┘  └──────────────┘  └─────────────┘
    
    LCD 2x16 CONNECTION (separate interface):
    ┌─────────────────────────────────────────────────────────────┐
    │                    LCD HD44780                              │
    │  D4-D7: Data (4-bit mode) sau D0-D7 (8-bit mode)          │
    │  RS: Register Select      (PC6)                             │
    │  EN: Enable              (PC7)                             │
    │  RW: Read/Write          (GND - doar scriere)              │
    └─────────────────────────────────────────────────────────────┘
```

## 3. Logica de decodificare adrese

### 3.1 Decodificarea memoriei

```
    Address Decoding Logic:
    
    Memory Select = /M_IO * (Address Range)
    
    EPROM_CS = /M_IO * /A19 * /A18 * /A17
    SRAM_CS  = /M_IO * /A19 * /A18 * A17
    
    Implementare cu 74HC138:
    ┌─────────────────────────────────────┐
    │          74HC138                    │
    │  A17  ──► A                         │
    │  A18  ──► B           Y0 ──► EPROM_CS │
    │  A19  ──► C           Y1 ──► SRAM_CS  │
    │  /M_IO ──► G1          Y2 ──► (ext)   │
    │  GND  ──► G2A         ...            │
    │  VCC  ──► G2B                       │
    └─────────────────────────────────────┘
```

### 3.2 Decodificarea I/O

```
    I/O Address Decoding:
    
    I/O_Select = M_IO * (Address Range)
    
    8251_CS = M_IO * Address_Match_8251 * Switch_S1
    8255_CS = M_IO * Address_Match_8255 * Switch_S2
    
    Implementare:
    ┌─────────────────────────────────────────┐
    │    Address Comparator + Switch Logic    │
    │                                         │
    │  A4-A15 ──► Comparator ──► 8251_CS     │
    │     +           +              +        │
    │   S1_SW  ──► Logic  ──► 8255_CS        │
    │   S2_SW                                 │
    └─────────────────────────────────────────┘
```

## 4. Semnalele de control

### 4.1 Bus Control Signals

```
    8086 Control Signals:
    ┌──────────┬─────────────────────────────────────────────┐
    │ Semnal   │               Funcție                       │
    ├──────────┼─────────────────────────────────────────────┤
    │ ALE      │ Address Latch Enable (74HC373)              │
    │ RD       │ Read strobe (active low)                    │
    │ WR       │ Write strobe (active low)                   │
    │ M/IO     │ Memory(0) / I/O(1) select                   │
    │ DEN      │ Data Enable for transceivers                │
    │ DT/R     │ Data Transmit(1) / Receive(0)              │
    └──────────┴─────────────────────────────────────────────┘
```

### 4.2 Timing Relationships

```
    Bus Cycle Timing:
    
    CLK    ___     ___     ___     ___
           ___│   │___│   │___│   │___
    
    ALE    _____           _____________
               │___│_______│
    
    Addr   XXXXXXX│valid│XXXXXXXXX│valid│XX
           ──────────────────────────────────
    
    RD/WR  ─────────────────│   │─────────
                           │___│
    
    Data   ZZZZZZZZZZZZ│valid│ZZZZZZZZZZZ
           ────────────────────────────────
```

## 5. Considerații de implementare

### 5.1 Alimentarea sistemului

```
    Power Distribution:
    ┌─────────────────────────────────────────────────────────────┐
    │                    +5V POWER RAIL                          │
    │  ┌─────────────┬─────────────┬─────────────┬──────────────┐ │
    │  │    CPU      │   MEMORY    │    I/O      │ PERIPHERALS  │ │
    │  │   ~1.2A     │   ~0.5A     │   ~0.3A     │    ~0.5A     │ │
    │  │             │             │             │              │ │
    │  │  ┌─────┐    │ ┌─────┐     │  ┌─────┐    │   ┌─────┐    │ │
    │  │  │100nF│    │ │100nF│     │  │100nF│    │   │100nF│    │ │
    │  │  └─────┘    │ └─────┘     │  └─────┘    │   └─────┘    │ │
    │  └─────────────┴─────────────┴─────────────┴──────────────┘ │
    │                       DECOUPLING                             │
    └─────────────────────────────────────────────────────────────┘
    
    Total System Current: ~2.5A @ 5V
```

### 5.2 Clock System

```
    Clock Generation:
    
    ┌────────────────────────────────────────────────────────┐
    │              CRYSTAL OSCILLATOR                        │
    │                                                        │
    │     ┌─────┐    22pF                                   │
    │  ──►│     │◄─────────○                               │
    │     │ 8MHz│           │                               │
    │     │XTAL │           │    74HC04                     │
    │  ──►│     │◄──────────┼────┬───►│>○───► CLK (to 8086) │
    │     └─────┘           │    │                          │
    │                       │    │     1MΩ                  │
    │                  22pF │    └──────────┐               │
    │                       │               │               │
    │                       └───────────────┘               │
    └────────────────────────────────────────────────────────┘
```

Această arhitectură oferă o bază solidă pentru implementarea microsistemului cu 8086, respectând toate cerințele din temă și oferind flexibilitate pentru dezvoltarea ulterioară.