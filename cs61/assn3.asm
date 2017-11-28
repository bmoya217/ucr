;=================================================
; 
; Name: Branden Moya
; Username: bmoya001    
;
; SID: 861121591
; Assignment name: <assn 3>
; Lab section: 21
; TA: Bryan Marsh
;
; I hereby certify that I have not received 
; assistance on this assignment, or used code,
; from ANY outside source other than the
; instruction team. 
;
;=================================================

; for(i = 15 downto 0):
; if (bit[i] is a 0):
; print a 0
; else:
; print a 1
; shift left


.ORIG x3000
;Instructions
LD R6, CONVERT_ADDR		; R6 <-- Address pointer for Convert
LDR R1, R6, #0			; R1 <-- VARIABLE Convert 
LD R5, COUNTER          ; R5 <---COUNTER

ADD R2, R2, #12         ; R2 <---COUNTER FOR SPACES
NOT R2, R2
ADD R2, R2, #1

LOOP_DE_LOOP
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

BRzp LOOP_DE_LOOP

LEA R0, NEWLINE
PUTS

HALT
	
;Data
CONVERT_ADDR .FILL x5000 ; The address of where to find the data
COUNTER .FILL #15
ZERO .STRINGZ "0"
ONE .STRINGZ "1"
NEWLINE .STRINGZ "\n"
SPACE .STRINGZ " "
 

; Remote data
.ORIG x5000
CONVERT .FILL xABCD ; <----!!!NUMBER TO BE CONVERTED TO BINARY!!!

.END
