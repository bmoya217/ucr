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

LOOP_DE_LOOP
STR R2, R1, #0
ADD R2,R2,#1
ADD R1,R1,#1

ADD R4, R2, R3
BRn LOOP_DE_LOOP

LDR R1,R4, #7
STR R1,R2, #0

HALT

;Local data
POINTER .FILL x4000
COUNTER .FILL 0
CHECKER .FILL #-10



;Remote Data
.Orig x4000
ARRAY .BLKW #10


.end