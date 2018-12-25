TITLE L10 - Parameter Passing

; Ben Sebring
; section 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Goal: Demonstrate the ability to pass parameters into and out of a subroutine.
; Method: In a subroutine used to calculate the area of a trapezoid, convert the global variables into
;	parameters that extract the values from the stack and return the result through the stack.

INCLUDE Irvine32.inc
.data
area		REAL8 ?		; result of calculation
top			REAL8 ?		; top of trapezoid
bottom		REAL8 ?		; bottom of trapezoid
height		REAL8 ?		; height of trapezoid
b1prompt	BYTE "Enter the length of the top",0dh,0ah,0
b2prompt	BYTE "Enter the length of the bottom",0dh,0ah,0
hprompt		BYTE "Enter the height",0dh,0ah,0
result		BYTE "The area of the trapezoid is ",0

.code
main PROC
	finit					; initialize the floating point stack
	mov edx,OFFSET b1prompt	; address of message
	call WriteString		; write bottom prompt
	call ReadFloat			; read length of bottom
	fstp top					; save base
	mov edx,OFFSET b2prompt	; address of message
	call WriteString		; write top prompt
	call ReadFloat			; read length of top
	fstp bottom				; save base	
	mov edx,OFFSET hprompt	; address of message
	call WriteString		; write height prompt
	call ReadFloat			; read height
	fstp height				; save base	
	push OFFSET area		; call subroutine to calculate area
	push OFFSET height
	push OFFSET bottom
	push OFFSET top
	call trapezoid
	mov edx,OFFSET result	; address of message
	call WriteString		; write height prompt
	fld area				; write area of trapezoid
	call WriteFloat
	fstp area				; clear stack
	call CrLf
	call WaitMsg
	exit
main ENDP
.data
two			REAL8 2.0		; constant
.code
trapezoid PROC
; calculation of the area of a trapezoid
; Receives from stack
;	$top = length of top [REAL8 reference parameters]
;	$bottom = length of bottom [REAL8 reference parameters]
;	$height = length of height [REAL8 reference parameters]
; Returns
;	$area = area of trapezoid [REAL8 reference parameters]
PARAMS	= (2+1)*TYPE DWORD ; number of temporaries plus return address
NPARAMS = 4
$top    = PARAMS+0*TYPE DWORD
$bottom = PARAMS+1*TYPE DWORD
$height = PARAMS+2*TYPE DWORD
$area   = PARAMS+3*TYPE DWORD
	push ebx
	pushfd
	; compute area
;*** convert each of the global variables into parameters
	mov ebx, $top[esp]
	fld REAL8 PTR [ebx]			; load top
	mov ebx, $bottom[esp]
	fadd REAL8 PTR [ebx]		; add bottom
	mov ebx, $height[esp]
	fmul REAL8 PTR [ebx]		; multiply by height
	fdiv two				; complete by averaging top and bottom
	mov ebx, $area[esp]
	fstp REAL8 PTR [ebx]
	pop ebx
	popfd					; restore flags
	ret NPARAMS*TYPE DWORD		; return and pop parameters
trapezoid ENDP
END main
