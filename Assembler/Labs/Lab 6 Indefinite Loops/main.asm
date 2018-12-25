TITLE L06 - Indefinite Loops

; Ben Sebring
; section 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Goal: Demonstrate the ability to repeat operations and to
;	manipulate characters.
; Method: Enter the parameters of a line,
;	Enter the x coordinate and calculate the height of the line.
;	Repeat the calculation as needed.
;
; 	The Irvine looping directives may not be used.
;	Correct use of character values.

INCLUDE Irvine32.inc
.data

y			SDWORD ?	; result of calculation
m			SDWORD ?	; slope of line
x			SDWORD ?	; x coordinate
b			SDWORD ?	; y intercept
mprompt		BYTE "Enter the slope of the line",0dh,0ah,0
bprompt		BYTE "Enter the intercept of the line",0dh,0ah,0
xprompt		BYTE "Enter the x coordinate",0dh,0ah,0
error		BYTE "Overflow, calculation aborted",0dh,0ah,0
result		BYTE "Y=",0
continue	BYTE "Repeat for another coordinate? (y/n)",0dh,0ah,0

.code
main PROC
;	Enter slope
	mov edx,OFFSET mprompt		; address of prompt
	call WriteString			; write prompt
	call ReadInt				; read number
	mov m,eax					; save value
;	Enter intercept
	mov edx,OFFSET bprompt		; address of prompt
	call WriteString			; write prompt
	call ReadInt				; read number
	mov b,eax					; save value
;*** Initialize the loop by loading a character into AL (Do NOT read)
	mov al, 'y'	

;*** Create a WHILE-DO loop based on the character in AL
while_loop:
	cmp al, 'y'					; checking condition for the loop
	jne end_loop				; Break out of loop if the did not enter a y

;	Enter coordinate
	mov edx,OFFSET xprompt		; address of coordinate prompt
	call WriteString			; write prompt
	call ReadInt				; read number
	mov x,eax					; save value
	imul m						; multiply by slope of line
	jno else_branch				; test for overflow
	mov edx,OFFSET error		; address of error message
	call WriteString			; write message
	jmp end_if					; skip other branch
else_branch:					; continue calculation
	add eax,b					; add intercept
	mov y,eax					; save result
	mov edx,OFFSET result		; address of result message
	call WriteString			; write message
	mov eax,y					; reload result
	call WriteInt				; write result
	call CrLf					; terminate line
end_if:							; target of branch
	mov	edx,OFFSET continue		; address of prompt message
	call WriteString			; write message

;*** Read the next character
	call ReadChar				; Reads a character into the al register
	call WriteChar				; Used to echo the read character to the console
	call CrLf					; Irvine
	jmp while_loop				; repeat loop body

;*** Terminate the WHILE-DO loop
end_loop:
	call WaitMsg
	exit
main ENDP
END main
