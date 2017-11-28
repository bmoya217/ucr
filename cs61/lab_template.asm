;===============================================================================
; Name: Moya, Branden
; Username: bmoya001@ucr.edu
; 
; Lab: lab 9.1
; Lab section: 021
; TA: Bryan Marsh
; 
;===============================================================================
.Orig x3000

;Instructions
LD R6, POINTER

ADD R0,R0,#10
ADD R0,R0,#-1
ST R6, POINTER
BRzp #-3

HALT

;Local data
POINTER .FILL x4000

;-------------------------------------------------------------------------------
; Subroutine: SUB_INSERT_NAME
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
SUB_INSERT_NAME
ST R7, R7_3200


LD R7, R7_3200
RET

;Subroutine data
R7_3200 .BLKW #1


;Remote Data
ARRAY .BLKW #100

.end