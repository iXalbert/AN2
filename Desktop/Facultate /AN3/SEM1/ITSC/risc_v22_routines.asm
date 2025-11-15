; RISC Simulator v2.2 — Utility Routines
; Conventions:
;  - Arguments: R0=n, R1=m (base), R2=k (base dst)
;  - Returns:   FindMinMax -> R3=min, R4=max; Factorial -> R0=result
;  - I/O:       INP Rx,2 reads byte; OUT Rx,4 writes value
;  - Calls via: JMS label; return via RET

            ORG 0x0010

; -----------------------------------------------------------------------------
; ReadArr(n=R0, m=R1): reads n values from input and stores sequentially at [m..]
; Destroys: R0,R1,R6
; -----------------------------------------------------------------------------
READ_ARR:
READ_LOOP:
            SUB     R0,#1
            BLO     READ_DONE
            INP     R6,2
            STR     R6,R1        ; [R1] = R6
            ADD     R1,#1        ; m++
            JMP     READ_LOOP
READ_DONE:  RET

; -----------------------------------------------------------------------------
; WriteArr(n=R0, m=R1): writes n values from memory [m..] to output
; Destroys: R0,R1,R6
; -----------------------------------------------------------------------------
WRITE_ARR:
WRITE_LOOP:
            SUB     R0,#1
            BLO     WRITE_DONE
            LDR     R6,R1        ; R6 = [R1]
            OUT     R6,4         ; print value
            ADD     R1,#1
            JMP     WRITE_LOOP
WRITE_DONE: RET

; -----------------------------------------------------------------------------
; FindMinMax(n=R0, m=R1): scans array and returns R3=min, R4=max
; Edge case: n==0 => min=0, max=0
; Destroys: R0,R1,R6
; -----------------------------------------------------------------------------
FIND_MIN_MAX:
            CMP     R0,#0
            BEQ     FM_ZERO
            ; initialize with first element
            LDR     R6,R1
            MOV     R3,R6        ; min
            MOV     R4,R6        ; max
            ADD     R1,#1
FM_LOOP:
            SUB     R0,#1
            BLO     FM_DONE
            LDR     R6,R1
            CMP     R6,R3
            BLO     FM_SET_MIN
            CMP     R6,R4
            BGE     FM_SET_MAX
            JMP     FM_NEXT
FM_SET_MIN: MOV     R3,R6
            JMP     FM_NEXT
FM_SET_MAX: MOV     R4,R6
FM_NEXT:    ADD     R1,#1
            JMP     FM_LOOP
FM_ZERO:    MOV     R3,#0
            MOV     R4,#0
FM_DONE:    RET

; -----------------------------------------------------------------------------
; PrintVal(n=R0): prints signed value in R0 (delegates to OUT port 4)
; -----------------------------------------------------------------------------
PRINT_VAL:
            OUT     R0,4
            RET

; -----------------------------------------------------------------------------
; DupArray(n=R0, m=R1, k=R2): duplicates array m->k skipping values equal to
;                             the array's min and max
; Uses: calls FIND_MIN_MAX; returns nothing (writes to dst)
; Destroys: R0,R1,R2,R3,R4,R6
; -----------------------------------------------------------------------------
DUP_ARRAY:
            ; save inputs
            STR     R0,SAVE_N
            STR     R1,SAVE_M
            ; find min/max
            JMS     FIND_MIN_MAX
            ; R3=min, R4=max
            STR     R3,MIN_VAL
            STR     R4,MAX_VAL
            ; restore n, m; keep k in R2
            LDR     R0,SAVE_N
            LDR     R1,SAVE_M
DUP_LOOP:
            SUB     R0,#1
            BLO     DUP_DONE
            LDR     R6,R1
            CMP     R6,R3        ; equal to min?
            BEQ     DUP_SKIP
            CMP     R6,R4        ; equal to max?
            BEQ     DUP_SKIP
            STR     R6,R2        ; store and advance dest
            ADD     R2,#1
DUP_SKIP:   ADD     R1,#1         ; advance src
            JMP     DUP_LOOP
DUP_DONE:   RET

; -----------------------------------------------------------------------------
; Factorial(n=R0): computes n! recursively using call stack
; Result in R0; n<2 => 1
; Destroys: R0,R5,R6
; -----------------------------------------------------------------------------
FACTORIAL:
            CMP     R0,#2
            BLO     FACT_BASE     ; if n < 2: return 1
            MOV     R5,R0         ; save n
            SUB     R0,#1
            JMS     FACTORIAL     ; R0 = fact(n-1)
            ; multiply R0 by saved n (R5) via repeated addition
            MOV     R6,#0
FACT_MUL:   SUB     R5,#1
            BLO     FACT_MUL_DONE
            ADD     R6,R0
            JMP     FACT_MUL
FACT_MUL_DONE:
            MOV     R0,R6
            RET
FACT_BASE:  MOV     R0,#1
            RET

; -----------------------------------------------------------------------------
; Optional demo main (comment out if linking elsewhere)
; Reads N, base M, and base K from memory and demonstrates routines
; -----------------------------------------------------------------------------
MAIN:
            ; Example usage (expects caller to set N,M,K in memory)
            LDR     R0,N
            LDR     R1,M
            JMS     READ_ARR      ; read N values into [M..]

            ; Find and print min/max
            LDR     R0,N
            LDR     R1,M
            JMS     FIND_MIN_MAX
            MOV     R0,R3
            JMS     PRINT_VAL
            MOV     R0,R4
            JMS     PRINT_VAL

            ; Duplicate without min/max into K and write out
            LDR     R0,N
            LDR     R1,M
            LDR     R2,K
            JMS     DUP_ARRAY
            ; For demo, write out N values from K (some may be skipped/leftover)
            LDR     R0,N
            LDR     R1,K
            JMS     WRITE_ARR

            ; Factorial demo: compute fact(N) and print
            LDR     R0,N
            JMS     FACTORIAL
            JMS     PRINT_VAL

            HLT

; -----------------------------------------------------------------------------
; Data section
; -----------------------------------------------------------------------------
            ORG 0x0100
N:          DAT 0          ; number of elements
M:          DAT 0          ; base address of source array
K:          DAT 0          ; base address of destination array
SAVE_N:     DAT 0
SAVE_M:     DAT 0
MIN_VAL:    DAT 0
MAX_VAL:    DAT 0
