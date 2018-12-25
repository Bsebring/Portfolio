TITLE L02 - Unsigned Integer

; Ben Sebring
; 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Goal: Demonstrate the ability to perform calculations using unsigned integers,
;	ignoring the possibility of overflow.
;
; Method: Compute the area of a circle producing a 32 bit result.
;	area=radius*radius*22/7
;
;	The result must be in the standard registers for division.
;	Store the whole part of the answer in a variable.
;	All values must be unsigned integers.
;	The result must be a positive, unsigned numbers.
;	Direct addressing is required for all shape parameters.
;	Immediate addressing may be used for formula constants.

INCLUDE Irvine32.inc
.data
;*** Declare 32 bit variables for all quantities named in the formula.
area	DWORD	?
radius	DWORD	500

.code
main PROC
	mov		eax,radius ;*** Calculate the area.
	mov		edx,0		;clear edx register
	mul		radius
	mov		ecx,22		;load 22 into ecx
	mul		ecx			;multiply by 22
	mov		ebx,7		;load 7 into ebx
	div		ebx			;divide by 7
	mov		area,eax	;load eax register into area
	

	;*** NOTE: Division requires special initialization.
	;*** NOTE: 22/7 cannot be stored in a variable or register.
	call DumpRegs
	call WaitMsg
	exit
main ENDP
END main
