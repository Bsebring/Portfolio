TITLE L04 - Conditional Operations

; Ben Sebring
; Section 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Goal: Demonstrate the ability to control the execution of the program with conditinal branching.
; Method: Enter the user's age and print a message telling the user if they are eligible to drive.
;	Drivers must be at least 16 years old.
;

INCLUDE Irvine32.inc
.data 
age		DWORD 0		; value to test
prompt	BYTE "Please enter your age",0dh,0ah,0
yes		BYTE "You are old enough to drive.",0dh,0ah,0
no		BYTE "Sorry, you are not old enough to drive.",0dh,0ah,0
.code
main PROC
	mov edx,OFFSET prompt	; address of message
	call WriteString		; write prompt
	call ReadDec			; read number
	mov age,eax			; save value
;*** create the IF-THEN-ELSE to load the address of the message to print

	cmp age,16				; compare age to 16
	jb else_branch			; jump to the else branch if below 16
	mov edx, OFFSET yes		; if age is above or eual to 16, load the address of string yes
	jmp end_if				; then jump to the end if the if-then-else statement
else_branch:				; executed if age is below 16
	mov edx, OFFSET no		; Load the address of string yes
end_if:						; end if the statement
	
	call WriteString		; write eligability message
	call WaitMsg
	exit
main ENDP
END main
