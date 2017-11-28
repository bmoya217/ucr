;=================================================
; Name: Moya, Branden
; Username: bmoya001@ucr.edu
; 
; Lab: lab 1
; Lab section: 021
; TA: Bryan Marsh
; 
;=================================================



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

; output
; for(i = 15 downto 0):
; if (bit[i] is a 0):
; print a 0
; else:
; print a 1
; shift left
LD R6, POINTER      	; R6 <-- Address pointer for Convert
LD R4, COUNTER

LARGERLOOP

LEA R0, B
PUTS

AND R1, R1, #0
AND R2, R2, #0

LDR R1, R6, #0			; R1 <-- VARIABLE Convert 
LD R5, COUNTER2         ; R5 <---COUNTER

ADD R2, R2, #12         ; R2 <---COUNTER FOR SPACES
NOT R2, R2
ADD R2, R2, #1

LOOP
ADD R1,R1,#0
BRn NEGATIVE
    
;POSITIVE
LEA R0, ZERO
PUTS
BR NEXT

;NEGATIVE
NEGATIVE
LEA R0, ONE
PUTS

NEXT

ADD R3, R2, R5
BRnp NEXT2

ADD R2,R2,#4
BRp NEXT2
LEA R0, SPACE
PUTS

NEXT2

ADD R1, R1, R1
ADD R5, R5, #-1

BRzp LOOP

LEA R0, NEWLINE
PUTS

ADD R4, R4, #1
ADD R6, R6, #1
LD R0, CHECKER
ADD R0, R0, R4
BRn LARGERLOOP

HALT
	
;Data

;Local data
POINTER .FILL x4000
COUNTER .FILL 1
CHECKER .FILL #-11

COUNTER2 .FILL #15
ZERO .STRINGZ "0"
ONE .STRINGZ "1"
NEWLINE .STRINGZ "\n"
SPACE .STRINGZ " "
B .STRINGZ "b"
 

; Remote data
.ORIG x4000
ARRAY .BLKW #10

.END