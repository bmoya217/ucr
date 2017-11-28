;===============================================================================
; Name: Moya, Branden
; Username: bmoya001@ucr.edu
; 
; Lab: lab 8.1
; Lab section: 021
; TA: Bryan Marsh
; 
;===============================================================================

;-------------------------------------------------------------------------------
; Test Harness for SUB_TO_UPPER subroutine:
; 
; (1) R0 ← Some address where we will store a user-input string
; (2) Call SUB_TO_UPPER subroutine
; (3) Trap x22 (i.e. print out the now-uppercase string)
;-------------------------------------------------------------------------------
.Orig x3000

;Instructions
LD R0, POINTER
JSR SUB_TO_UPPER
TRAP x22

HALT

;Local data
POINTER .FILL x4000

;-------------------------------------------------------------------------------
; Subroutine: SUB_TO_UPPER
; Parameter (R0): Address to store a string at
; Postcondition: The subroutine has allowed the user to input a string,
; terminated by the [ENTER] key, has converted the string
; to upper-case, and has stored it in a null-terminated array that
; starts at (R0).
; Return Value: R0 ← The address of the now upper case string.
;-------------------------------------------------------------------------------
.ORIG x3200
SUB_TO_UPPER
ST R0, R0_3200
LD R1, R0_3200
LD R2, CONVERT
LD R3, CHECK_A
LD R4, CHECK_Z
ST R7, R7_3200


GET_STRING_LOOP
    GETC                ;GET INPUT
    OUT
    
    ADD R7,R0,#-10      ;CHECKS FOR ENTER
        BRz GET_STRING_FINISH
    
    STR R0,R1,#0
    
    ADD R1,R1,#1
BR GET_STRING_LOOP

GET_STRING_FINISH
AND R7,R7,#0
STR R7,R1,#0

LD R1, R0_3200
LDR R0,R1,#0
TO_UPPER_LOOP
    ADD R7,R0,R3
        BRn SKIP_CONVERSION
    ADD R7,R0,R4
        BRp SKIP_CONVERSION
    
    AND R0,R0,R2
    STR R0,R1,#0
    SKIP_CONVERSION
    
    ADD R1,R1,#1
    LDR R0,R1,#0
BRnp TO_UPPER_LOOP

LD R0, R0_3200
LD R7, R7_3200
RET

;Subroutine data
R0_3200 .BLKW #1
R7_3200 .BLKW #1
CHECK_A .FILL #-97
CHECK_Z .FILL #-122
CONVERT .FILL x005F

;Remote data
.ORIG x4000
ARRAY .FILL 0

.end