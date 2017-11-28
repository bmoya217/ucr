;=================================================
; Name: Moya, Branden
; Username: bmoya001@ucr.edu
; 
; Lab: lab 1
; Lab section: 021
; TA: Bryan Marsh
; 
;=================================================
.Orig x3000

;Instructions
LEA R0, PROMPT
PUTS
GETC
OUT

JSR PARITY_CHECK_3200

LEA R0, OUTPUT
PUTS
ADD R0,R1,#0
OUT

HALT

;LOCAL DATA
PROMPT .STRINGZ "\nENTER NUMBER TO PARITY CHECK: "
OUTPUT .STRINGZ "\nTHE NUMBER OF 1's IS: "

;=================================================
;subroutine:PARITY CHECK (COUNT THE 1s)
;input:R0 IS THE SINGLE CHAR TO COUNT
;post condition:THE NUMBER OF 1s IN A BINARY NUM
;return values:R1 WILL HAVE THE NUM  OF ONES
;=================================================
.ORIG x3200
PARITY_CHECK_3200
ST R7,STORE_R7
LD R2, COUNTER
AND R1,R1,#0

LEFT_SHIFT
    AND R0,R0,R0
    BRzp SKIP
        ADD R1,R1,#1
    SKIP
    
    ADD R0,R0,R0
    ADD R2,R2,#1
BRn LEFT_SHIFT

LD R7, NUM_TO_CHAR
ADD R1,R1,R7

LD R7, STORE_R7
RET

;SUBROUTINE DATA
NUM_TO_CHAR .FILL #48
COUNTER .FILL #-16
STORE_R7 .FILL #0

.end