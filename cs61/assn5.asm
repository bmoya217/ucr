;=================================================
; Name: Moya, Branden
; Username: bmoya001@ucr.edu
; 
; Assignment name: assn5
; Lab section: 021
; TA: Bryan Marsh
;
; I hereby certify that I have not recieved 
; assistance on this assignment, or used code, from
; ANY outside source other than the instuction team.
;
;=================================================
.ORIG x3000

;INSTRUCTIONS
JSR GET_INPUT_3200
ST R1, NUM1

JSR GET_INPUT_3200
ST R1, NUM2

LD R1, NUM1
JSR OUTPUT_3400

LEA R0, P1
PUTS

LD R1, NUM2
JSR OUTPUT_3400

LEA R0, P2
PUTS

LD R1, NUM1
LD R2, NUM2
LD R3, POINTER_3600
JSRR R3

LEA R0, P3
PUTS

HALT

;LOCAL DATA
NUM1 .FILL #0
NUM2 .FILL #0
P1 .STRINGZ " * "
P2 .STRINGZ " = "
P3 .STRINGZ "\n"
POINTER_3600 .FILL x3600

;=================================================
;subroutine:dgets input
;input:none
;post condition:stores input in r1 as decimal
;return values:r1 stores the input
.Orig x3200
GET_INPUT_3200                            ;NAME
ST R2, R2_3200
ST R7, R7_3200             ;STORES R7,R2 VALUES FOR BACKUP
LD R3, ONE_CHECK

START
AND R1,R1,#0
AND R5,R5,#0			;RESETS VALUES
AND R6,R6,#0
LD R4, FIVE

LEA R0, PROMPT			;OUPUTS PROMPT
PUTS

GET_INPUT				;GETS INPUT AND CONVERTS IT TO A SINGLE NUMBER IN R1
	GETC
	OUT
	
	BR TEST_INPUT
	BACK 
	
	LD R2, NINE
	ADD R6,R1,#0		;SETS R6 TO R0 FOR MULTIPLICATION
	INNER
		ADD R1,R1,R6
		BRn ERROR
		ADD R2,R2,#-1
	BRp INNER
	ADD R0,R0,R3
	ADD R1,R1,R0		;ADDS THE NEXT NUMBER
	BRn ERROR
	
	ADD R6,R6,#2
	ADD R4,R4,#-1
BRp GET_INPUT
BR ALMOST_DONE

TEST_INPUT
	LD R2, ENTER		;CHECKS FOR ENTER BAR
	ADD R2,R2,R0
	BRz LAST_CHECK
	
	ADD R2,R6,#-1
	BRzp NUM_CHECK
	
	LD R2, MINUS		;CHECKS FOR '-'
	ADD R2,R2,R0
	BRz NEGATIVE
	
	LD R2, PLUS			;CHECKS FOR '+'
	ADD R2,R2,R0
	BRz POSITIVE
	
	NUM_CHECK
	LD R2, ONE_CHECK	;CHECKS FOR < 1
	ADD R2,R2,R0
	BRn ERROR
	
	LD R2, NINE_CHECK	;CHECKS FOR > 9
	ADD R2,R2,R0
	BRp ERROR
BR BACK

NEGATIVE				;IF '-'
	ADD R5,R5,#-1
	ADD R6,R6,#1
BR GET_INPUT

POSITIVE				;IF '+'
	ADD R5,R5,#1
	ADD R6,R6,#1
BR GET_INPUT

NEGATE					;NEGATES R1 IF NEGATIVE SIGN WAS ENTERED
NOT R1,R1
ADD R1,R1,#1
BR FINISH

	LAST_CHECK
		ADD R2,R6,#-1
		BRn ERROR
		
		AND R5,R5,R5
		BRnp LAST_LAST_CHECK
		BR FINISH
		
		LAST_LAST_CHECK
			ADD R2,R6,#-2
		BRn ERROR
		
		AND R5,R5,R5
		BRn NEGATE
	BR FINISH

	ERROR				;ERROR OUTPUT/REASK FOR NUMBERS
		LD R2, ENTER
		ADD R2,R2,R0
		BRnp NEW_LINE 
		BACK_TO_ERROR
		LEA R0, WRONG
		PUTS
	BR START
	
	NEW_LINE
		AND R0,R0,#0
		ADD R0,R0,#10
		OUT
	BR BACK_TO_ERROR
ALMOST_DONE
	AND R0,R0,#0
	ADD R0,R0,#10
	OUT
FINISH

LD R2, R2_3200
LD R7, R7_3200              ;RESETS VAULES

RET

;Subroutine data
R2_3200 .BLKW #1
R7_3200 .BLKW #1
PROMPT .STRINGZ "Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"
WRONG .STRINGZ "ERROR INVALID INPUT\n"
PLUS .FILL #-43
MINUS .FILL #-45
ENTER .FILL #-10
ONE_CHECK .FILL #-48	;TEST IF CHAR IS POSITIVE AFTER
NINE_CHECK .FILL #-57	;TEST IF CHAR IS NEGATIVE AFTER
ONE .FILL #1
NINE .FILL #9
FIVE.FILL #5

;=================================================
;subroutine:PRINT IN decinmal
;input:R1 TO BE PRINTED IN decimal
;post condition:OUTPUT
;return values:NONE
.Orig x3400
OUTPUT_3400               ;NAME
ST R7, R7_3400             ;STORES R7,R5,R2 VALUES FOR BACKUP
LD R3, POINTER
LD R4, NUM_TO_CHAR
AND R5,R5,#0
ADD R5,R5,#5                ;COUNTER
AND R6,R6,#0

AND R1,R1,R1
BRz OUTPUT_ZERO
BRp SKIP1_3400
NOT R1,R1
ADD R1,R1,#1
LD R0, MINUSOUT
OUT
BR LOOP1

SKIP1_3400
LD R0, PLUSOUT
OUT

LOOP1
LDR R2,R3,#0
AND R0,R0,#0


LOOP2
ADD R1,R1,R2
BRn SKIP
ADD R0,R0,#1
ADD R6,R6,#1
BR LOOP2
SKIP
AND R6,R6,R6
BRz SKIP2

ADD R0,R0,R4
OUT

SKIP2

NOT R2,R2
ADD R2,R2,#1
ADD R1,R1,R2

ADD R3,R3,#1

ADD R5,R5,#-1
BRp LOOP1

BR SKIP2_3400

OUTPUT_ZERO
LD R0, SERO
OUT
SKIP2_3400

LD R7, R7_3400              ;RESETS VAULES
RET

;Subroutine data
R7_3400 .FILL #0
NUM_TO_CHAR .FILL x30
POINTER .FILL x3500

.ORIG x3500
TEN_THOUSAND .FILL #-10000
THOUSAND .FILL #-1000
HOUNDRED .FILL #-100
TEN .FILL #-10
ONE1 .FILL #-1
SERO .FILL #48
PLUSOUT .FILL '+'
MINUSOUT .FILL '-'

;=================================================
;subroutine:MULTIPLY
;input:MULTIPLY R1 AND R2 STORE IN R1
;post condition:R1*R2=R1
;return values:R1 AND R6 IS THE VALUE OF THE SIGN
.Orig x3600
MULTIPLY_3600                            ;NAME
AND R0,R0,#0
AND R3,R3,#0
AND R4,R4,#0
AND R5,R5,#0
AND R6,R6,#0                ; NEGATIVE ONLY IF R6 = 1
ST R7, R7_3600             ;STORES R7 VALUES FOR BACKUP

AND R1,R1,R1                ;CHECKS SIGNS OF R1 AND R2 AND MAKES THEM POSITIVE
BRz ZERO					; also checks to see if r1 or r2 are zero
BRp SKIP1_3600
	NOT R1,R1
	ADD R1,R1,#1
	ADD R6,R6,#1
SKIP1_3600
AND R2,R2,R2
BRz ZERO
BRp SKIP2_3600
	ADD R6,R6,#1
	NOT R2,R2
	ADD R2,R2,#1
SKIP2_3600

NOT R1,R1					;puts the smaller in r1 and the larger in r2
ADD R1,R1,#1
ADD R0,R1,R2
NOT R1,R1
ADD R1,R1,#1
AND R0,R0,R0
BRp SKIP3_3600				;skip if already in right regeistars
	AND R0,R1,R1
	AND R1,R2,R2
	AND R2,R0,R0
SKIP3_3600

ADD R0,R1,#-1				;checks if r1 is one
BRz ONE_3600

ADD R0,R1,#0				;sets r0 to be the counter
AND R1,R1,#0				;and r1 to be the result

LOOPDELOOP					;multiplies
ADD R1,R1,R2
BRn ERROR_3600
ADD R0,R0,#-1
BRp LOOPDELOOP
BR FINISH_3600

	ZERO						;if a zero was in r1 or r2
		AND R1,R1,#0
	BR FINISH_3600
	
	ONE_3600					;if a 1 was in r1 set larger value as result
		AND R1,R2,R2
	BR FINISH_3600
	
	ERROR_3600					;overflow!
		LEA R0, EPROMPT
		PUTS
	BR SKIP4_3600
	
	FINISH_3600
	
	ADD R6,R6,#-1				;NEGATIVE IF DIFFERENT SIGNS
	BRnp SKIP5_3600				;skip if result is positive
		NOT R1,R1
		ADD R1,R1,#1

SKIP5_3600
	
JSR OUTPUT_3400

SKIP4_3600
LD R7, R7_3600              ;RESETS VAULES
RET

;Subroutine data
R7_3600 .FILL #0
EPROMPT .STRINGZ "Overflow!"
.END