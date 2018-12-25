TITLE L07 - Floating Point

; Ben Sebring
; Section 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Goal: Demonstrate the ability to perform floating point operations.
; Method: Calculate the area of a hexagon using floating point values and operations.
;	area=3*sqrt(3)/2*R*R

INCLUDE Irvine32.inc
.data
area		REAL8 ?		; result of calculation
radius		REAL8 ?		; radius of inscribed circle
two			REAL8 2.0	; constant
three		REAL8 3.0	; constant
rprompt	BYTE "Enter the radius of the hexagon",0dh,0ah,0
result		BYTE "The area of the hexagon is ",0

.code
main PROC
	finit					; initialize the floating point stack
	mov edx,OFFSET rprompt	; address of message
	call WriteString		; write radius prompt
	call ReadFloat			; read radius of hexagon
	fstp radius				; save base of figure

;*** calculate area, storing it in area and leaving it on the top of the stack
	fld three				; Loading 3.0 into S(0)
	fsqrt					; getting sqrt of 3 still in S(0)
	fld three				; Loading 3.0 onto list
	fmul					; 3*sqrt(3)
	fdiv two				; dividing 3*sqrt(3)
	fld radius				; Adding radius to the list
	fmul					; Multiplying
	fld radius				; Adding radius to the list
	fmul					; Multiplying
	fst area				; Stroing area, and leaving it on the list

	mov edx,OFFSET result	; address of message
	call WriteString		; write height prompt
	call WriteFloat
	call CrLf
	call WaitMsg
	exit
main ENDP
END main
