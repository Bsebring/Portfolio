TITLE L09 Definite Loops

; Ben Sebring
; Section 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Assignment: Demonstrate the use of counter loops
; Description: Compute the terms of an arithmetic series, zeno's series 1/2+1/4+1/8...


INCLUDE Irvine32.inc
.data
factor		SDWORD 2 ; factor to compute term
term		DWORD ? ; number of terms to calculate
; Note: seeds 0,1 produce the Fibanocci Sequence
sum			REAL8 0.0 ; value to test
prompt		BYTE "Enter number number of sequence to generate (0 to terminate):",0dh,0ah,0
message	BYTE "The sum is ",0

.code
main PROC
next:
	mov edx,OFFSET prompt	; address of message for term to generate
	call WriteString		; write message
	call ReadDec			; read number
	cmp eax,0				; test if done series of numbers
	je quit					; exit if done
	mov term,eax			; save term number
	mov ecx,eax				; initialize counter
	finit
;*** Create a counted loop for the instructions between the labels for_loop and end_for
for_loop:
	fld1					; calculate term
	fild factor
	fdiv
	fadd sum				; add to sum
	fstp sum
	mov eax,factor			; double factor
	add factor,eax
	loopnz for_loop			; decrement ecx and loop if not zero
end_for:
	mov edx,OFFSET message	; address of result message
	call WriteString		; write message
	fld sum
	call WriteFloat			; write number
	call CrLf				; output end of line
	fldz					; reinitialize vaiables
	fstp sum
	mov factor,2
	jmp next				; repeat for another number

quit:
	call WaitMsg
	exit
main ENDP
; PLACE ADDITIONAL PROCEDURES HERE
END main
