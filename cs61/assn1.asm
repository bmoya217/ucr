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

;=================================================
; REG VALUES 	R0  R1  R2  R3  R4  R5  R6  R7
;=================================================
; PRE-LOOP	00  06  12  00  00  00  00  1168	
;ITERATION 1	00  05  12  12  00  00  00  1168
;ITERATION 2	00  04  12  24  00  00  00  1168
;ITERATION 3	00  03  12  36  00  00  00  1168
;ITERATION 4	00  02  12  48  00  00  00  1168
;ITERATION 5	00  01  12  60  00  00  00  1168
;ITERATION 6	00  00  12  72  00  00  00  1168
;ENDofPROGRAM	00  00  12  72  00  00  00  DEC_0
;=================================================



.ORIG x3000

;INSTRUCTIONS
	LD R1, DEC_0
	LD R2, DEC_12
	LD R3, DEC_6

	DO_WHILE_LOOP
		ADD R1, R1, R2
		ADD R3, R3, #-1
		BRp DO_WHILE_LOOP
	END_DO_WHILE_LOOP

	HALT

;LOCAL DATA
	DEC_0 .FILL #0
	DEC_12 .FILL #12
	DEC_6 .FILL #6

.END
