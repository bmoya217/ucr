;=================================================
; Name: Moya, Branden
; Username:bmoya001@ucr.edu
; 
; Lab: assn 2
; Lab section: 021
; TA: Bryan Marsh
; 
; I hereby certify that I have not received
; assistance on this assignment, or used code, 
; from ANY outside source other than the
; instruction team.
;=================================================
.ORIG x3000

;Instructions
LEA R0, PROMPT ;outputs the prompt string
PUTS

GETC ;gets the first input
OUT ;echos the number back to user
ADD R1, R0, #0 ;sets the number to register 1
LD R0, NEW_LINE ;loads newline ascii to register 0
OUT ;outputs a new line

GETC ;same for second number
OUT
ADD R2, R0, #0
LD R0, NEW_LINE
OUT

ADD R0, R1, #0
OUT
LEA R0, OUTPUT
PUTS
ADD R0, R2, #0
OUT
LEA R0, OUTPUT2
PUTS

;MATH ISH
LD R4, CHAR ;R4 = 48
NOT R5, R2
ADD R5, R5, R1
ADD R5, R5, #1

BRn NEGATIVE

POSITIVE
    NOT R2, R2  ; negates r2 using twos compliment
    ADD R2,R2,#1

BR COMPUTE

NEGATIVE
    NOT R1,R1
    ADD R1,R1,#1
    LEA R0, NEG
    PUTS

COMPUTE
ADD R3, R1, R2 ;r1 - r2
ADD R0, R3, R4
OUT
LD R0, NEW_LINE
OUT

HALT

;Data
PROMPT .STRINGZ "ENTER two numbers (i.e '0'....'9')\n"
NEW_LINE .FILL x0A
CHAR .FILL   #48
NEG .STRINGZ "-"
OUTPUT .STRINGZ " - "
OUTPUT2 .STRINGZ " = "

.end