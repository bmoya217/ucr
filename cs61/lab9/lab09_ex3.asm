;===============================================================================
; Name: Moya, Branden
; Username: bmoya001@ucr.edu
; 
; Lab: lab 9.2
; Lab section: 021
; TA: Bryan Marsh
; 
;===============================================================================
.ORIG x3000

;Instructions
LD R1, POINTER      ;STACK ADDRESS
LD R2, POINTER      ;TOP
LD R3, CAPACITY
LD R4, ASCII_DOWN

GETC
OUT
ADD R0,R0,R4
JSR SUB_STACK_PUSH
LD R0, SPACE
OUT
GETC
OUT
ADD R0,R0,R4
JSR SUB_STACK_PUSH
LD R0, SPACE
OUT
GETC
OUT
AND R0,R0,#0
ADD R0,R0,#10
OUT

JSR SUB_RPN_MULTIPLY

HALT

;Local data
POINTER .FILL x4000
CAPACITY .FILL #10
SPACE .FILL x20
ASCII_DOWN .FILL #-48

;-------------------------------------------------------------------------------
; Subroutine: SUB_STACK_PUSH
; Parameter (R0): The value to push onto the stack
; Parameter (R1): stack_addr: A pointer to the beginning of the stack
; Parameter (R2): top: A pointer to the next place to PUSH an item
; Parameter (R3): capacity: The number of additional items the stack can hold
; Postcondition: The subroutine has pushed (R0) onto the stack. If an overflow
; occurred, the subroutine has printed an overflow error message
; and terminated.
; Return Value: R2 ← updated top value
; R3 ← updated capacity value
;-------------------------------------------------------------------------------
.ORIG x3200
SUB_STACK_PUSH
ST R7, R7_3200

AND R3,R3,R3
    BRz STACK_FULL

ADD R2,R2,#1
STR R0,R2,#0
ADD R3,R3,#-1
BR DONE1
    
STACK_FULL
    LEA R0, PUSH_ERROR
    PUTS

DONE1
    LD R7, R7_3200
    RET

;Subroutine data
R7_3200 .BLKW #1
PUSH_ERROR .STRINGZ "ERROR: OVERFLOW!\n"

;-------------------------------------------------------------------------------
; Subroutine: SUB_RPN_MULTIPLY
; Parameter (R1): stack_addr
; Parameter (R2): top
; Parameter (R3): capacity
; Postcondition: The subroutine has popped off the top two values of the stack,
; multiplied them together, and pushed the resulting value back
; onto the stack.
; Return Value: R2 ← updated top value
; R3 ← updated capacity value
;-------------------------------------------------------------------------------
.ORIG x3400
SUB_RPN_MULTIPLY
;INSTRUCTIONS
ST R7, R7_3400

JSR SUB_STACK_POP       ;GETS VALUES AND STORS IN R4 AND R5
AND R4,R0,R0
JSR SUB_STACK_POP
AND R5,R0,R0
BRz ZERO
AND R4,R4,R4
BRz ZERO

AND R0,R0,#0
MULTIPLY_LOOP
    ADD R0,R0,R5
    ADD R4,R4,#-1
BRp MULTIPLY_LOOP
BR FINISH

ZERO
    AND R0,R0,#0

FINISH
    JSR SUB_STACK_PUSH
    AND R5,R5,#0
    JSR PRINT_NUM
    LD R7, R7_3400
    RET

;Subroutine data
R7_3400 .BLKW #1


;-------------------------------------------------------------------------------
; Subroutine: SUB_STACK_POP
; Parameter (R1): stack_addr: A pointer to the beginning of the stack
; Parameter (R2): top: A pointer to the item to POP
; Parameter (R3): capacity: The # of additional items the stack can hold
; Postcondition: The subroutine has popped MEM[top] off of the stack.
; If an underflow occurred, the subroutine has printed an
; underflow error message and terminated.
; Return Value: R0 ← value popped off of the stack
; R2 ← updated top value
; R3 ← updated capacity value
;-------------------------------------------------------------------------------
.ORIG x3600
SUB_STACK_POP
ST R7, R7_3600

NOT R7,R1
ADD R7,R7,#1
ADD R7,R7,R2
    BRz STACK_EMPTY

LDR R0,R2,#0
ADD R2,R2,#-1
ADD R3,R3,#1
BR DONE
    
STACK_EMPTY
    LEA R0, POP_ERROR
    PUTS

DONE
    LD R7, R7_3600
    RET

;Subroutine data
R7_3600 .BLKW #1
POP_ERROR .STRINGZ "ERROR: UNDERFLOW!\n"

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
.orig x3800
PRINT_NUM

;Instructions
ST R7, R7_3800
LD R6, ASCII_UP

AND R5,R5,#0
JSR SUB_STACK_POP

TENS_LOOP
    ADD R7,R0,#-10
        BRn LESSTHANTEN
    AND R0,R7,R7
    ADD R5,R5,#1
BR TENS_LOOP

LESSTHANTEN
    AND R5,R5,R5
    BRz FINISH38
    AND R4,R0,R0
    ADD R0,R5,R6
    OUT
    AND R0,R4,R4
    
FINISH38
    ADD R0,R0,R6
    OUT
    AND R0,R0,#0
    ADD R0,R0,#10
    OUT
    LD R7, R7_3800
    RET
    
;Instructions
R7_3800 .BLKW #1             ;STORES R7,R5,R2 VALUES FOR BACKUP
ASCII_UP .FILL x30

;Remote Data
.ORIG x4001
ARRAY .BLKW #10

.end