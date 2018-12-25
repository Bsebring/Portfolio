TITLE L17 - Conditional Assembly

; Ben Sebring
; Section 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Goal: Demonstrate the ability to use macros.
; Method: Create a macro to implement the conversion from host (Littleendian) 
;	order to network (Bigendian) order.

INCLUDE Irvine32.inc
LITTLE_ENDIAN EQU TRUE
;*** Assemble and run this program twice. Once with the above equate active and second time with it deleted or commented out.
h2nl MACRO value
;*** Start a conditional asseembly directive to test if the label LITTLE_ENDIAN exists
IFDEF LITTLE_ENDIAN
	push eax		; save registers
	push ebx
	xor eax,eax		; clear register
	mov ebx,value	; load value
	mov al,bl		; move value byte
	rol eax,8		; shift result bits to make room for new data
	ror ebx,8		; shift value bits in opposite direction
	mov al,bl		; move s byte
	rol eax,8		; shift result bits to make room for new data
	ror ebx,8		; shift value bits in opposite direction
	mov al,bl		; move value byte
	rol eax,8		; shift result bits to make room for new data
	ror ebx,8		; shift value bits in opposite direction
	mov al,bl		; move value byte
	mov value,eax	; output new value
	pop ebx			; restore registers
	pop eax
;*** End the conditional assembly directive
ENDIF
	ENDM h2nl
;***
.data
data	DWORD 0a1b2c3d4h	; value to swap
before	BYTE "Before:",0
after	BYTE "After: ",0

.code
main PROC
	mov edx,OFFSET before	; print begining of line
	call WriteString
	mov eax,data	; print value before
	call WriteHex
	call CrLf
	h2nl data
	mov edx,OFFSET after	; print begining of line
	call WriteString
	mov eax,data	; print value before
	call WriteHex
	call CrLf
	call WaitMsg
	exit
main ENDP
END main
