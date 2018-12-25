

INCLUDE Irvine32.inc
INCLUDE quadratic.inc
.data
a0			REAL8 ?		; parabola parameters
b0			REAL8 ?
c0			REAL8 ?
r1			REAL8 ?		; roots of the parabola
r2			REAL8 ?		; roots of the parabola
prompt		BYTE "Enter the parameters of the parabola separated by spaces",0dh,0ah,0
message		BYTE "Roots: ",0

.code
main PROC
	finit
	mov edx,OFFSET prompt ; prompt for parameters
	call WriteString
	call ReadFloat		; Read a
	fstp a0
	call ReadFloat		; Read b
	fstp b0
	call ReadFloat		; Read c
	fstp c0
	INVOKE quadratic,0,OFFSET a0,OFFSET b0,OFFSET c0,OFFSET r1
	mov edx,OFFSET message ; print message
	call WriteString
	fld r1				; print postive root
	call WriteFloat
	fstp r1
	mov al,','			; print a seperator space
	call WriteChar
	mov al,' '			; print a seperator space
	call WriteChar
	INVOKE quadratic,1,OFFSET a0,OFFSET b0,OFFSET c0,OFFSET r2
	fld r2				; print first root
	call WriteFloat
	fstp r2
	call CrLf
	call WaitMsg	; hold display window open
	exit
main ENDP
END main