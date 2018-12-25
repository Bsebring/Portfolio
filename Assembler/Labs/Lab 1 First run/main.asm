TITLE L01 - First Run

; Ben Sebring
; 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Goal: Demonstrate the ability to manipulate 4 unsigned integers
;
; Method: Write a program to add/subtract a series of values.
;	Included both addition and subtraction instructions.
;	The number of MOV, ADD and SUB instructions must be exactly 4.
;	All values must be unsigned integers.
;	The result must be a positive, unsigned number.
;	One of the values must be greater than 16 bits.
;	Immediate addressing is required for all values.
;	The result must be in the EAX register.

INCLUDE Irvine32.inc
.data

.code
main PROC
	;*** put manipulation instructions here
	mov    EAX,1		; load first value (1)
	add    EAX,70000	; add 70000 to eax register
	sub    EAX,5000		; subtract 5,000 from eax register
	add    EAX,10		; add 10 to eax register
	call DumpRegs
	call WaitMsg
	exit
main ENDP
END main
