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

JSR SUB_STACK_POP

HALT

;Local data
POINTER .FILL x4000
CAPACITY .FILL #10

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
.ORIG x3200
SUB_STACK_POP
ST R7, R7_3200

NOT R7,R1
ADD R7,R7,#1
ADD R7,R7,R2
    BRz STACK_EMPTY

LDR R0,R2,#0
ADD R2,R2,#-1
ADD R3,R3,#1
BR DONE
    
STACK_EMPTY
    LEA R0, PUSH_ERROR
    PUTS

DONE
    LD R7, R7_3200
    RET

;Subroutine data
R7_3200 .BLKW #1
PUSH_ERROR .STRINGZ "ERROR: UNDERFLOW!\n"

;Remote Data
.ORIG x4000
ARRAY .BLKW #10

.end