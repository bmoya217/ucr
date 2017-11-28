;===============================================================================
; Name: Moya, Branden
; Username: bmoya001@ucr.edu
; 
; Lab: lab 9.1
; Lab section: 021
; TA: Bryan Marsh
; 
;===============================================================================
.ORIG x3000

;Instructions
LD R1, POINTER      ;STACK ADDRESS
LD R2, POINTER      ;TOP
LD R3, CAPACITY

GETC

JSR SUB_STACK_PUSH

HALT

;Local data
POINTER .FILL x4000
CAPACITY .FILL #10

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

STR R0,R2,#0
ADD R2,R2,#1
ADD R3,R3,#-1
BR DONE
    
STACK_FULL
    LEA R0, PUSH_ERROR
    PUTS

DONE
    LD R7, R7_3200
    RET

;Subroutine data
R7_3200 .BLKW #1
PUSH_ERROR .STRINGZ "ERROR: OVERFLOW!\n"

;Remote Data
.ORIG x4000
ARRAY .BLKW #10

.end