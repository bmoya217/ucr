;=================================================
; Name: Moya, Branden
; Username: bmoya001@ucr.edu
; 
; Lab: lab 7.1
; Lab section: 021
; TA: Bryan Marsh
; 
;=================================================
.Orig x3000
;Instructions
LD R0, POINTER
JSR GET_STRING_3200
PUTS

HALT

;Local data
POINTER .FILL x3100

;-----------------------------------------------
; Subroutine: SUB_GET_STRING
; Parameter (R0): The address of where to start storing the string
; Postcondition: The subroutine has allowed the user to input a string,
; terminated by the [ENTER] key, and has stored it in an array
; that starts at (R0) and is NULL-terminated.
; Return Value: R5 The number of non-sentinel characters read from the user
;-----------------------------------------------
.ORIG x3200
GET_STRING_3200
ST R0, GET_STRING_R0
AND R1,R0,R0
AND R5,R5,#0
ST R7, GET_STRING_R7

LEA R0, GET_STRING_PROMPT
PUTS

GET_STRING_LOOP
    GETC                ;GET INPUT
    OUT
    
    ADD R7,R0,#-10      ;CHECKS FOR ENTER
    BRz GET_STRING_FINISH
    
    STR R0,R1,#0
    
    ADD R1,R1,#1
    ADD R5,R5,#1
BR GET_STRING_LOOP

GET_STRING_FINISH
AND R7,R7,#0
STR R7,R1,#0

LD R0, GET_STRING_R0
LD R7, GET_STRING_R7
RET

;Subroutine data
GET_STRING_R0 .BLKW #1
GET_STRING_R7 .BLKW #1
GET_STRING_PROMPT .STRINGZ "ENTER WORDS AND TERMINATE STRING WITH 'ENTER':\n"

.end