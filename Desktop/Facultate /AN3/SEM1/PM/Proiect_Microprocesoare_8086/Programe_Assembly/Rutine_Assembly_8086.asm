; ===============================================================================
; RUTINE ASSEMBLY PENTRU MICROSISTEMUL 8086
; Proiect: Microsistem cu microprocesorul 8086
; Student: Albert Rosca
; Anul universitar: 2025-2026
; ===============================================================================

; Definirea constantelor pentru adrese I/O
; Adresele pentru 8255 (configurabile cu S2)
PPI_BASE_1      EQU     0250H          ; Adresa de bază când S2=0
PPI_BASE_2      EQU     0A50H          ; Adresa de bază când S2=1
PPI_PORTA       EQU     0              ; Offset pentru Port A
PPI_PORTB       EQU     1              ; Offset pentru Port B
PPI_PORTC       EQU     2              ; Offset pentru Port C
PPI_CONTROL     EQU     3              ; Offset pentru Control Register

; Adresele pentru 8251 (configurabile cu S1)
USART_BASE_1    EQU     04D0H          ; Adresa de bază când S1=0
USART_BASE_2    EQU     05D0H          ; Adresa de bază când S1=1
USART_DATA      EQU     0              ; Offset pentru Data Register
USART_STATUS    EQU     1              ; Offset pentru Status Register
USART_CONTROL   EQU     1              ; Offset pentru Control Register (same as status)

; Constantele pentru configurarea 8255
PPI_MODE0_ALL   EQU     80H            ; Toate porturile în Modul 0, ieșiri
PPI_MODE0_A_IN  EQU     90H            ; Port A intrare, B și C ieșiri
PPI_MODE0_B_IN  EQU     82H            ; Port B intrare, A și C ieșiri

; Constantele pentru configurarea 8251
USART_MODE      EQU     4EH            ; 8 biți, 1 stop bit, no parity, x16 clock
USART_COMMAND   EQU     37H            ; Enable TX, RX, reset error flags

.CODE

; ===============================================================================
; 1. RUTINA DE PROGRAMARE A CIRCUITULUI 8255
; ===============================================================================
INIT_8255 PROC NEAR
    ; Intrări: BX = adresa de bază a 8255 (PPI_BASE_1 sau PPI_BASE_2)
    ; Ieșiri: Niciuna
    ; Registre modificate: AX, DX
    
    PUSH    AX              ; Salvează registrele
    PUSH    DX
    
    ; Setează adresa registrului de control
    MOV     DX, BX          ; DX = adresa de bază
    ADD     DX, PPI_CONTROL ; DX = adresa registrului de control
    
    ; Configurează 8255
    ; Port A: intrare (pentru tastatură - coloane)  
    ; Port B: ieșire (pentru LED-uri)
    ; Port C: ieșire (pentru control 7-segmente și tastatura - linii)
    MOV     AL, PPI_MODE0_A_IN
    OUT     DX, AL          ; Scrie comanda de configurare
    
    POP     DX              ; Restaurează registrele
    POP     AX
    RET
INIT_8255 ENDP

; ===============================================================================
; 2. RUTINA DE PROGRAMARE A CIRCUITULUI 8251
; ===============================================================================
INIT_8251 PROC NEAR
    ; Intrări: BX = adresa de bază a 8251 (USART_BASE_1 sau USART_BASE_2)
    ; Ieșiri: Niciuna
    ; Registre modificate: AX, DX, CX
    
    PUSH    AX              ; Salvează registrele
    PUSH    DX
    PUSH    CX
    
    ; Reset 8251
    MOV     DX, BX
    ADD     DX, USART_CONTROL
    MOV     AL, 0           ; Dummy write pentru reset
    OUT     DX, AL
    OUT     DX, AL
    OUT     DX, AL
    
    ; Configurează modul de operare
    MOV     AL, USART_MODE  ; 8 biți, 1 stop, no parity, x16
    OUT     DX, AL
    
    ; Configurează comanda
    MOV     AL, USART_COMMAND ; Enable TX/RX
    OUT     DX, AL
    
    POP     CX              ; Restaurează registrele
    POP     DX
    POP     AX
    RET
INIT_8251 ENDP

; ===============================================================================
; 3. RUTINA DE EMISIE CARACTER PE INTERFAȚA SERIALĂ
; ===============================================================================
SERIAL_SEND PROC NEAR
    ; Intrări: AL = caracterul de transmis
    ;          BX = adresa de bază a 8251
    ; Ieșiri: Niciuna
    ; Registre modificate: DX, AH
    
    PUSH    AX              ; Salvează registrele
    PUSH    DX
    
    MOV     AH, AL          ; Salvează caracterul în AH
    MOV     DX, BX
    ADD     DX, USART_STATUS ; DX = adresa registrului de status
    
WAIT_TX_READY:
    IN      AL, DX          ; Citește statusul
    TEST    AL, 01H         ; Testează bitul TXRDY
    JZ      WAIT_TX_READY   ; Dacă nu e gata, așteaptă
    
    ; Transmite caracterul
    MOV     DX, BX
    ADD     DX, USART_DATA  ; DX = adresa registrului de date
    MOV     AL, AH          ; Recuperează caracterul
    OUT     DX, AL          ; Transmite caracterul
    
    POP     DX              ; Restaurează registrele
    POP     AX
    RET
SERIAL_SEND ENDP

; ===============================================================================
; 4. RUTINA DE RECEPȚIE CARACTER PE INTERFAȚA SERIALĂ
; ===============================================================================
SERIAL_RECEIVE PROC NEAR
    ; Intrări: BX = adresa de bază a 8251
    ; Ieșiri: AL = caracterul recepționat
    ; Registre modificate: AL, DX
    
    PUSH    DX              ; Salvează registrul
    
    MOV     DX, BX
    ADD     DX, USART_STATUS ; DX = adresa registrului de status
    
WAIT_RX_READY:
    IN      AL, DX          ; Citește statusul
    TEST    AL, 02H         ; Testează bitul RXRDY
    JZ      WAIT_RX_READY   ; Dacă nu e gata, așteaptă
    
    ; Citește caracterul
    MOV     DX, BX
    ADD     DX, USART_DATA  ; DX = adresa registrului de date
    IN      AL, DX          ; Citește caracterul
    
    POP     DX              ; Restaurează registrul
    RET
SERIAL_RECEIVE ENDP

; ===============================================================================
; 5. RUTINA DE EMISIE CARACTER PE INTERFAȚA PARALELĂ
; ===============================================================================
PARALLEL_SEND PROC NEAR
    ; Intrări: AL = caracterul de transmis
    ;          BX = adresa de bază a 8255
    ; Ieșiri: Niciuna
    ; Registre modificate: DX
    
    PUSH    DX              ; Salvează registrul
    
    MOV     DX, BX
    ADD     DX, PPI_PORTB   ; DX = adresa Port B
    OUT     DX, AL          ; Trimite caracterul pe Port B
    
    ; Generează impuls pe PC0 pentru semnalul STROBE
    MOV     DX, BX
    ADD     DX, PPI_PORTC   ; DX = adresa Port C
    IN      AL, DX          ; Citește Port C
    OR      AL, 01H         ; Setează PC0 = 1
    OUT     DX, AL
    
    ; Scurt delay
    MOV     CX, 100
DELAY_LOOP:
    LOOP    DELAY_LOOP
    
    IN      AL, DX          ; Citește din nou Port C
    AND     AL, 0FEH        ; Resetează PC0 = 0
    OUT     DX, AL
    
    POP     DX              ; Restaurează registrul
    RET
PARALLEL_SEND ENDP

; ===============================================================================
; 6. RUTINA DE SCANARE A MINITASTATURII
; ===============================================================================
SCAN_KEYBOARD PROC NEAR
    ; Intrări: BX = adresa de bază a 8255
    ; Ieșiri: AL = codul tastei apăsate (0 dacă nicio tastă)
    ;         Format: bit 7-4 = rând, bit 3-0 = coloană
    ; Registre modificate: AL, DX, CX, AH
    
    PUSH    DX              ; Salvează registrele
    PUSH    CX
    PUSH    AH
    
    MOV     AH, 0           ; AH = codul tastei găsite
    MOV     CL, 0           ; CL = indexul rândului curent
    
SCAN_ROW_LOOP:
    ; Activează rândul curent (trimite '0' pe linia respectivă)
    MOV     AL, 0FFH        ; Toate liniile inactive (1)
    MOV     CH, CL          ; CH = indexul rândului
    MOV     DL, 1
    SHL     DL, CH          ; DL = masca pentru rândul curent
    NOT     DL              ; Inversează masca
    AND     AL, DL          ; Activează rândul curent (0)
    
    ; Trimite pe Port C (liniile tastaturii)
    MOV     DX, BX
    ADD     DX, PPI_PORTC
    OUT     DX, AL
    
    ; Scurt delay pentru stabilizare
    PUSH    CX
    MOV     CX, 50
STAB_DELAY:
    LOOP    STAB_DELAY
    POP     CX
    
    ; Citește coloanele de pe Port A
    MOV     DX, BX
    ADD     DX, PPI_PORTA
    IN      AL, DX
    
    ; Verifică care coloană este activă (0)
    MOV     DL, 0           ; DL = indexul coloanei
    MOV     DH, AL          ; DH = valoarea citită
    
CHECK_COL_LOOP:
    TEST    DH, 01H         ; Testează LSB
    JZ      KEY_FOUND       ; Dacă e 0, tastă găsită
    
    SHR     DH, 1           ; Shift right pentru următoarea coloană
    INC     DL              ; Incrementează indexul coloanei
    CMP     DL, 3           ; Verifică toate cele 3 coloane
    JL      CHECK_COL_LOOP
    
    ; Nicio tastă găsită pe rândul curent, încearcă următorul
    INC     CL              ; Următorul rând
    CMP     CL, 3           ; Verifică toate cele 3 rânduri
    JL      SCAN_ROW_LOOP
    
    ; Nicio tastă găsită
    MOV     AL, 0
    JMP     SCAN_END
    
KEY_FOUND:
    ; Calculează codul tastei: rând * 16 + coloană
    MOV     AL, CL          ; AL = rândul
    SHL     AL, 4           ; AL = rând * 16
    ADD     AL, DL          ; AL = rând * 16 + coloană
    
SCAN_END:
    ; Dezactivează toate rândurile
    MOV     DX, BX
    ADD     DX, PPI_PORTC
    MOV     DH, 0FFH
    OUT     DX, DH
    
    POP     AH              ; Restaurează registrele
    POP     CX
    POP     DX
    RET
SCAN_KEYBOARD ENDP

; ===============================================================================
; 7. RUTINA DE APRINDERE/STINGERE LED
; ===============================================================================
CONTROL_LEDS PROC NEAR
    ; Intrări: AL = masca LED-urilor (bit 0-9 pentru LED 0-9)
    ;          BX = adresa de bază a 8255
    ; Ieșiri: Niciuna
    ; Registre modificate: DX, AH
    
    PUSH    DX              ; Salvează registrele
    PUSH    AH
    
    ; LED-uri 0-7 pe Port B
    MOV     DX, BX
    ADD     DX, PPI_PORTB
    OUT     DX, AL          ; Trimite primii 8 biți
    
    ; LED-uri 8-9 pe PC0-PC1
    MOV     DX, BX
    ADD     DX, PPI_PORTC
    IN      AH, DX          ; Citește Port C curent
    AND     AH, 0FCH        ; Păstrează doar biții 2-7
    
    MOV     DH, AL          ; DH = masca originală
    SHR     DH, 6           ; Shift cu 6 pentru a avea biții 8-9 în poziții 0-1
    AND     DH, 03H         ; Păstrează doar biții 0-1
    OR      AH, DH          ; Combină cu Port C
    
    OUT     DX, AH          ; Scrie în Port C
    
    POP     AH              ; Restaurează registrele
    POP     DX
    RET
CONTROL_LEDS ENDP

; ===============================================================================
; 8. RUTINA DE AFIȘARE CARACTER HEXA PE 7 SEGMENTE
; ===============================================================================
DISPLAY_HEX_7SEG PROC NEAR
    ; Intrări: AL = caracterul hexa (0-F)
    ;          BL = rangul de afișare (0-7)
    ;          BH = adresa de bază a 8255 (low byte)
    ; Ieșiri: Niciuna
    ; Registre modificate: DX, AH, CX
    
    PUSH    DX              ; Salvează registrele
    PUSH    AH
    PUSH    CX
    PUSH    SI
    
    ; Validează intrările
    AND     AL, 0FH         ; Limitează la 0-F
    AND     BL, 07H         ; Limitează la 0-7
    
    ; Obține codul pentru 7 segmente din tabelă
    MOV     AH, 0
    MOV     SI, AX
    MOV     AL, CS:HEX_7SEG_TABLE[SI]
    
    ; Trimite datele pe Port B
    MOV     DX, BH          ; DX = adresa de bază PPI
    ADD     DX, PPI_PORTB
    OUT     DX, AL
    
    ; Selectează rangul pe Port C (PC2-PC5)
    MOV     DX, BH
    ADD     DX, PPI_PORTC
    IN      AH, DX          ; Citește Port C curent
    AND     AH, 0C3H        ; Păstrează PC0-PC1 și PC6-PC7
    
    ; Calculează masca pentru rang (1 din 8 decoder)
    MOV     CL, BL
    MOV     CH, 1
    SHL     CH, CL          ; CH = 2^BL
    SHL     CH, 2           ; Shift la poziția PC2-PC5
    OR      AH, CH          ; Combină cu Port C
    
    OUT     DX, AH          ; Activează rangul selectat
    
    POP     SI              ; Restaurează registrele
    POP     CX
    POP     AH
    POP     DX
    RET
DISPLAY_HEX_7SEG ENDP

; ===============================================================================
; 9. TABELĂ DE CONVERSIE PENTRU 7 SEGMENTE (CATOD COMUN)
; ===============================================================================
HEX_7SEG_TABLE DB 3FH    ; 0: segments a,b,c,d,e,f
               DB 06H    ; 1: segments b,c  
               DB 5BH    ; 2: segments a,b,d,e,g
               DB 4FH    ; 3: segments a,b,c,d,g
               DB 66H    ; 4: segments b,c,f,g
               DB 6DH    ; 5: segments a,c,d,f,g
               DB 7DH    ; 6: segments a,c,d,e,f,g
               DB 07H    ; 7: segments a,b,c
               DB 7FH    ; 8: segments a,b,c,d,e,f,g
               DB 6FH    ; 9: segments a,b,c,d,f,g
               DB 77H    ; A: segments a,b,c,e,f,g
               DB 7CH    ; B: segments c,d,e,f,g
               DB 39H    ; C: segments a,d,e,f
               DB 5EH    ; D: segments b,c,d,e,g
               DB 79H    ; E: segments a,d,e,f,g
               DB 71H    ; F: segments a,e,f,g

; ===============================================================================
; 10. RUTINA DE INIȚIALIZARE SISTEM
; ===============================================================================
INIT_SYSTEM PROC NEAR
    ; Intrări: Niciuna
    ; Ieșiri: Niciuna
    ; Registre modificate: AX, BX, DX
    
    PUSH    AX              ; Salvează registrele
    PUSH    BX
    PUSH    DX
    
    ; Inițializează 8255 cu adresa implicită
    MOV     BX, PPI_BASE_1  ; Folosește prima adresă
    CALL    INIT_8255
    
    ; Inițializează 8251 cu adresa implicită  
    MOV     BX, USART_BASE_1 ; Folosește prima adresă
    CALL    INIT_8251
    
    ; Stinge toate LED-urile
    MOV     AL, 0           ; Toate LED-urile stinse
    MOV     BX, PPI_BASE_1
    CALL    CONTROL_LEDS
    
    ; Șterge afișajul 7 segmente
    MOV     AL, 0           ; Caracter gol
    MOV     BH, PPI_BASE_1 & 0FFH ; Low byte din adresa PPI
    MOV     BL, 0           ; Primul rang
    
CLEAR_DISPLAY_LOOP:
    CALL    DISPLAY_HEX_7SEG
    INC     BL              ; Următorul rang
    CMP     BL, 8
    JL      CLEAR_DISPLAY_LOOP
    
    POP     DX              ; Restaurează registrele
    POP     BX
    POP     AX
    RET
INIT_SYSTEM ENDP

; ===============================================================================
; 11. PROGRAM PRINCIPAL DE TEST
; ===============================================================================
MAIN PROC FAR
    ; Inițializează sistemul
    CALL    INIT_SYSTEM
    
    ; Bucla principală de test
TEST_LOOP:
    ; Scanează tastatura
    MOV     BX, PPI_BASE_1
    CALL    SCAN_KEYBOARD
    
    ; Dacă s-a apăsat o tastă, afișează codul pe 7-segmente
    CMP     AL, 0
    JZ      NO_KEY_PRESSED
    
    ; Afișează codul tastei pe primul rang
    MOV     BL, 0           ; Primul rang
    MOV     BH, PPI_BASE_1 & 0FFH
    CALL    DISPLAY_HEX_7SEG
    
    ; Aprinde LED-ul corespunzător
    MOV     AH, AL          ; Salvează codul
    MOV     AL, 1
    MOV     CL, AH
    AND     CL, 0FH         ; Limitează la 0-15
    SHL     AL, CL          ; 2^CL
    MOV     BX, PPI_BASE_1
    CALL    CONTROL_LEDS
    
    ; Trimite codul pe interfața serială
    MOV     AL, AH          ; Recuperează codul
    MOV     BX, USART_BASE_1
    CALL    SERIAL_SEND
    
NO_KEY_PRESSED:
    ; Delay pentru debouncing
    MOV     CX, 10000
MAIN_DELAY:
    LOOP    MAIN_DELAY
    
    JMP     TEST_LOOP       ; Repetă la infinit
    
MAIN ENDP

END MAIN