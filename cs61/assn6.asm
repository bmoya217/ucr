;=================================================
; Name: Moya, Branden
; Username: bmoya001@ucr.edu
; 
; Assignment name: assn1
; Lab section: 021
; TA: Bryan Marsh
;
; I hereby certify that I have not recieved 
; assistance on this assignment, or used code, from
; ANY outside source other than the instuction team.
;
;=================================================
.ORIG x3000			; Program begins here

;Instructions
LD R5, ASCII_UP
LD R6, BUSYNESS_POINTER                 ;THESE WILL REMAIN UNCHANGED

TOP
JSR MENU_3200

ADD R1,R1,#-1
    BRz CHOICE_1
ADD R1,R1,#-1
    BRz CHOICE_2
ADD R1,R1,#-1
    BRz CHOICE_3
ADD R1,R1,#-1
    BRz CHOICE_4
ADD R1,R1,#-1
    BRz CHOICE_5
ADD R1,R1,#-1
    BRz CHOICE_6
BR QUIT

CHOICE_1
    LDR R0,R6,#1
    JSRR R0
    AND R2,R2,R2
    BRp YEAH
    BR NAH

CHOICE_2
    LDR R0,R6,#2
    JSRR R0
    AND R2,R2,R2
    BRp YEAH_2
    BR NAH_2

CHOICE_3
    LDR R0,R6,#3
    JSRR R0
    LEA R0, BUSY_MACHINES
    PUTS
    LDR R0,R6,#8
    JSRR R0
    LEA R0, BUSY_MACHINES_2
    PUTS
    BR TOP

CHOICE_4
    LDR R0,R6,#4
    JSRR R0
    LEA R0, BUSY_MACHINES
    PUTS
    LDR R0,R6,#8
    JSRR R0
    LEA R0, FREE_MACHINES_2
    PUTS
    BR TOP

CHOICE_5
    LDR R0,R6,#7
    JSRR R0
    LDR R0,R6,#5
    JSRR R0    
    AND R2,R2,R2
    BRz BUSY_0
    BR FREE_0

CHOICE_6
    LDR R0,R6,#6
    JSRR R0    
    AND R1,R2,R2
    BRn LOST
    BR FOUND

YEAH_2
    AND R2,R1,R1
    LEA R0, ALL
    PUTS
    LEA R0, ARE_FREE
    PUTS
    BR TOP

NAH_2
    AND R2,R1,R1
    LEA R0, NOT_ALL
    PUTS
    LEA R0, ARE_FREE
    PUTS
    BR TOP

YEAH
    AND R2,R1,R1
    LEA R0, ALL
    PUTS
    LEA R0, ARE_BUSY
    PUTS
    BR TOP

NAH
    AND R2,R1,R1
    LEA R0, NOT_ALL
    PUTS
    LEA R0, ARE_BUSY
    PUTS
    BR TOP

FREE_0
    LEA R0, FREE
    PUTS
    AND R2,R1,R1
    LDR R0,R6,#8
    JSRR R0
    LEA R0, FREE_2
    PUTS
    BR TOP

BUSY_0
    LEA R0, FREE
    PUTS
    AND R2,R1,R1
    LDR R0,R6,#8
    JSRR R0
    LEA R0, BUSY_2
    PUTS
    BR TOP
    
LOST
    LEA R0, FIRST_0
    PUTS
    BR TOP
    
FOUND
    LEA R0, FIRST_1
    PUTS
    LDR R0,R6,#8
    JSRR R0
    LD R0, NEWLINE
    OUT
    BR TOP
    
QUIT
    LEA R0, GOODBYE
    PUTS 

    HALT
	
;Data
BUSYNESS_POINTER .FILL x5000
ASCII_UP .FILL #48
NEWLINE .FILL #10
ALL .STRINGZ "All"
NOT_ALL .STRINGZ "Not all"
ARE_FREE .STRINGZ " machines are free\n"
ARE_BUSY .STRINGZ " machines are busy\n"
BUSY_MACHINES .STRINGZ "There are "
BUSY_MACHINES_2 .STRINGZ " busy machines\n"
FREE_MACHINES_2 .STRINGZ " free machines\n"
FREE .STRINGZ "Machine "
FREE_2 .STRINGZ " is free\n"
BUSY_2 .STRINGZ " is busy\n"
FIRST_0 .STRINGZ "No machines are free\n"   ;//fixme ADD NEWLINE AFTER NUMBER
FIRST_1 .STRINGZ "The first available machine is number "
GOODBYE .STRINGZ "Goodbye!\n"

;-------------------------------------------------------------------------------
; Subroutine: MENU
; Inputs: None
; Postcondition: The subroutine has printed out a menu with numerical options, allowed the
;                          user to select an option, and returned the selected option.
; Return Value (R1): The option selected:  #1, #2, #3, #4, #5, #6 or #7
; no other return value is possible
;-------------------------------------------------------------------------------
.ORIG x3200
MENU_3200

;Instructions
ST R7, R7_3200

RESTART_3200
    LD R1, ASCII_DOWN
    LEA R0, MENU_PROMPT ;GET INPUT
    PUTS
    GETC
    ADD R7,R0,#-10
    BRz ERROR_3200
    OUT
    
    ADD R1,R1,R0        ;CHECK INPUT
    BRnz ERROR_3200
    ADD R7,R1,#-7
    BRnz FINISH_3200

ERROR_3200
    LEA R0, MENU_ERROR_MESSAGE
    PUTS
    BR RESTART_3200

FINISH_3200
    LD R0, TENNNN
    OUT
    AND R0,R0,#0
    LD R7, R7_3200
    RET

;Subroutine data
R7_3200 .BLKW #1
ASCII_DOWN .FILL #-48
TENNNN .FILL #10
MENU_ERROR_MESSAGE .STRINGZ "\nINVALID INPUT\n"
MENU_PROMPT .STRINGZ "***********************\n* The Busyness Server *\n***********************\n1. Check to see whether all machines are busy\n2. Check to see whether all machines are free\n3. Report the number of busy machines\n4. Report the number of free machines\n5. Report the status of machine n\n6. Report the number of the first available machine\n7. Quit\n"

;-------------------------------------------------------------------------------
; Subroutine: ALL_MACHINES_BUSY
; Inputs: None
; Postcondition: The subroutine has returned a value indicating whether all machines are busy
; Return value (R2): 1 if all machines are busy,    0 otherwise
;-------------------------------------------------------------------------------
.ORIG x3400
ALL_MACHINES_BUSY_3400

;Instructions
ST R7, R7_3400
AND R2,R2,#0

LDR R1,R6,#0
BRnp NOT_BUSY_3400
    ADD R2,R2,#1

NOT_BUSY_3400
    RET

;Subroutine data
R7_3400 .BLKW #1

;-------------------------------------------------------------------------------
; Subroutine: ALL_MACHINES_FREE
; Inputs: None
; Postcondition: The subroutine has returned a value indicating whether all machines are free
; Return value (R2): 1 if all machines are free,    0 otherwise
;-------------------------------------------------------------------------------
.ORIG x3600
ALL_MACHINES_FREE_3600

;Instructions
ST R7, R7_3600
LDR R1,R6,#0
ADD R1,R1,#1
BRnp NOT_FREE_3600
    ADD R2,R2,#1
    
NOT_FREE_3600
    AND R1,R1,#0
    LD R7,R7_3600
    RET
    
;Subroutine data
R7_3600 .BLKW #1

;-------------------------------------------------------------------------------
; Subroutine: NUM_BUSY_MACHINES
; Inputs: None
; Postcondition: The subroutine has returned the number of busy machines.
; Return Value (R2): The number of machines that are busy
;-------------------------------------------------------------------------------
.ORIG x3800
NUM_BUSY_MACHINES_3800

;Instructions
ST R7, R7_3800
AND R2,R2,#0
ADD R0,R2,#15

LDR R1,R6,#0
BRn LOOP_3800
    ADD R2,R2,#1

LOOP_3800               ;IF R1 IS EVER POSITIVE THEN R2++
    ADD R1,R1,R1        ;BECAUSE THAT MEANS THAT ITS BUSY
    BRn SKIP_3800
        ADD R2,R2,#1
    
    SKIP_3800
    ADD R0,R0,#-1    
BRp LOOP_3800


AND R1,R1,#0
LD R7,R7_3800
RET

;Subroutine data
R7_3800 .BLKW #1

;-------------------------------------------------------------------------------
; Subroutine: NUM_FREE_MACHINES
; Inputs: None
; Postcondition: The subroutine has returned the number of free machines
; Return Value (R2): The number of machines that are free 
;-------------------------------------------------------------------------------
.ORIG x3A00
NUM_FREE_MACHINES_3A00

;Instructions
ST R7, R7_3A00

JSR NUM_BUSY_MACHINES_3800  ;SUBTRACTS 16 AND NBMs TO GET THE FREE MACHINES
ADD R2,R2,#-16              ;eg.    5-16=-11
NOT R2,R2                   ;       !-11=10
ADD R2,R2,#1                ;       10+1=11

LD R7,R7_3A00
RET

;Subroutine data
R7_3A00 .BLKW #1

;-------------------------------------------------------------------------------
; Subroutine: MACHINE_STATUS
; Input (R1): Which machine to check
; Postcondition: The subroutine has returned a value indicating whether the machine indicated
;                          by (R1) is busy or not.
; Return Value (R2): 0 if machine (R1) is busy, 1 if it is free
;-------------------------------------------------------------------------------
.ORIG x3C00
MACHINE_STATUS_3C00

;Instructions
ST R1, R1_3C00
ST R7, R7_3C00
LDR R3,R6,#0
AND R2,R2,#0

ADD R1,R1,#-15      ;HOW MANY TIMES TO LEFT SHIFT
NOT R1,R1
ADD R1,R1,#1

BRp LOOP_3C00
    AND R3,R3,R3
        BRzp FINISH_3C00
            ADD R2,R2,#1
BR FINISH_3C00

LOOP_3C00
    ADD R3,R3,R3    
    ADD R1,R1,#-1    
BRp LOOP_3C00

AND R3,R3,R3
BRzp FINISH_3C00
    ADD R2,R2,#1

FINISH_3C00
    AND R1,R1,#0
    AND R3,R3,#0
    LD R1, R1_3C00
    LD R7, R7_3C00
    RET

;Subroutine data
R1_3C00 .BLKW #1
R7_3C00 .BLKW #1

;-------------------------------------------------------------------------------
; Subroutine: FIRST_FREE
; Inputs: None
; Postcondition: 
; The subroutine has returned a value indicating the lowest numbered free machine
; Return Value (R2): the number of the free machine
;-------------------------------------------------------------------------------
.ORIG x3E00
FIRST_FREE_3E00

;Instructions
ST R7, R7_3E00
AND R2,R2,#0
ADD R2,R2,#-1
ADD R0,R2,#15

LDR R1,R6,#0
BRzp LOOP_3E00
    AND R2,R0,R0

LOOP_3E00               ;IF R1 IS EVER NEG THEN R2 <= (R0)
    ADD R1,R1,R1        ;BECAUSE THAT MEANS THAT ITS FREE
    BRzp SKIP_3E00
        AND R2,R0,R0
    
    SKIP_3E00
    ADD R0,R0,#-1    
BRzp LOOP_3E00

AND R1,R1,#0
LD R7,R7_3E00
RET

;Subroutine data
R7_3E00 .BLKW #1

;-------------------------------------------------------------------------------
; Subroutine: Get input
; Inputs: None
; Postcondition: 
; The subroutine get up to a 5 digit input from the user within the range [-32768,32767]
; Return Value (R1): The value of the contructed input
; NOTE: This subroutine should be the same as the one that you did in assignment 5
;	to get input from the user, except the prompt is different.
;-------------------------------------------------------------------------------
.ORIG x4000
GET_INPUT_4000
ST R2, R2_4000
ST R5, R5_4000
ST R6, R6_4000
ST R7, R7_4000         	;STORES R7,R2 VALUES FOR BACKUP
LD R3, ONE_CHECK

START
    AND R1,R1,#0            ;RESETS VALUES
    AND R4,R4,#0        ;SIGN CHECK
    ADD R5,R4,#-1
    AND R6,R6,#0        ;NUM CHECK FOR ENTER

    LEA R0, PROMPT			;OUPUTS PROMPT
    PUTS
    
GET_INPUT				;GETS INPUT AND CONVERTS IT TO A SINGLE NUMBER IN R1
	GETC
	OUT
	AND R6,R6,R6
	    BRp NOT_FIRST
	
    LD R7, PLUS
    ADD R7,R7,R0
        BRz SIGN
    
    LD R7, MINUS
    ADD R7,R7,R0
        BRz NEGATIVE
        BR NOT_FIRST
    
    SIGN
        ADD R5,R5,#1
        BRp ERROR
        BR GET_INPUT
	
	NOT_FIRST
	ADD R7,R0,#-10      ;CHECKS FOR ENTER
        BRnp NOT_ENTER
    
    AND R6,R6,R6
        BRz ERROR_2
        
    AND R4,R4,R4
        BRp ERROR_2
        BR FINISH
    
    NOT_ENTER
    	ADD R0,R0,R3        ;CHECKS FOR < 0
            BRn ERROR
        
        ADD R7,R0,#-9       ;CHECKS FOR > 9
            BRp ERROR 
	
	ADD R6,R1,#0		;SETS R6 TO R0 FOR MULTIPLICATION
    LD R2, NINE
    INNER               ;MULTIPLIES BY 10
		ADD R1,R1,R6
		BRn ERROR
		ADD R2,R2,#-1
	BRp INNER
	
	ADD R1,R1,R0		;ADDS THE NEXT NUMBER TO PRODUCT
	ADD R7,R1,#-16
	BRzp ERROR
	
	ADD R6,R6,#1
BR GET_INPUT

ERROR				;ERROR OUTPUT/RE-ASK FOR NUMBERS
    AND R0,R0,#0
    ADD R0,R0,#10
    OUT
    
ERROR_2
    LEA R0, WRONG
	PUTS
    BR START
    
NEGATIVE
    ADD R4,R4,#1
    BR SIGN

FINISH
    LD R2, R2_4000
    LD R5, R5_4000
    LD R6, R6_4000
    LD R7, R7_4000              ;RESETS VAULES
    RET

;Subroutine data
R2_4000 .BLKW #1
R5_4000 .BLKW #1
R6_4000 .BLKW #1
R7_4000 .BLKW #1
PLUS .FILL #-43
MINUS .FILL #-45
ENTER .FILL #-10
ONE_CHECK .FILL #-48	;TEST IF CHAR IS POSITIVE AFTER
NINE .FILL #9
PROMPT .STRINGZ "Enter which machine you want the status of (0 - 15), followed by ENTER: "
WRONG .STRINGZ "ERROR INVALID INPUT\n"

;-------------------------------------------------------------------------------
; Subroutine: print number
; Inputs: 
; Postcondition: 
; The subroutine prints the number that is in R2
; Return Value : 
; NOTE: This subroutine should be the same as the one that you did in assignment 5
;	to print the number to the user WITHOUT leading 0's and DOES NOT output the '+' 
;	for positive numbers.
;-------------------------------------------------------------------------------
.orig x4200
PRINT_NUM_4200

;Instructions
ST R7, R7_4200

ADD R7,R2,#-10
BRn LESSTHANTEN
	ADD R0,R5,#1
	OUT
	
	ADD R2,R2,#-10
	
LESSTHANTEN
ADD R0,R2,R5
OUT

LD R7, R7_4200
RET
;Instructions
R7_4200 .BLKW #1             ;STORES R7,R5,R2 VALUES FOR BACKUP

;-------------------------------------------------------------------------------
;Remote data
.ORIG x5000			; Remote data
BUSYNESS .FILL xABCD		; <----!!!VALUE FOR BUSYNESS VECTOR!!!
SUBROUTINE_POINTER_1 .FILL x3400
SUBROUTINE_POINTER_2 .FILL x3600
SUBROUTINE_POINTER_3 .FILL x3800
SUBROUTINE_POINTER_4 .FILL x3A00
SUBROUTINE_POINTER_5 .FILL x3C00
SUBROUTINE_POINTER_6 .FILL x3E00
SUBROUTINE_POINTER_7 .FILL x4000
SUBROUTINE_POINTER_8 .FILL x4200

.END
