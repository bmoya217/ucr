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
AND R1,R1,#0

LD R1, POINTER
LD R2, COUNTER
LD R3, CHECKER
LD R4, COUNTER ;;2^n

LOOP_DE_LOOP

STR R4, R1, #0
ADD R2,R2,#1
ADD R1,R1,#1
ADD R4,R4,R4

ADD R0, R2, R3
BRn LOOP_DE_LOOP

LDR R1,R2, #7

HALT

;Local data
POINTER .FILL x4000
COUNTER .FILL 1
CHECKER .FILL #-11



;Remote Data
.Orig x4000
ARRAY .BLKW #10


.end