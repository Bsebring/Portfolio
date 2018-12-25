TITLE L05 - Signed Integer

; Ben Sebring
; Section 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Goal: Demonstrate the ability to make a decision on signed integers.
; Method: Enter the temperature and print a message classifying the temperature.
;
;	The program is able to print one of three possible messages.
;	Correct use of signed conditional branch instructions.
;	Correctly adjust for different value sizes.

INCLUDE Irvine32.inc
.data 
reference	SWORD -38		; value to test against
;*** Do NOT change the declaration of "reference". "reference" MUST be an SWORD.
value		SDWORD 0	; value to test
prompt		BYTE "Enter an integer temperature",0dh,0ah,0
above		BYTE "Your temperature is above the melting point of mercury",0dh,0ah,0
equal		BYTE "Your temperature is equal to the melting point of mercury",0dh,0ah,0
below		BYTE "Your temperature is below the melting point of mercury",0dh,0ah,0

.code
main PROC
	mov edx,OFFSET prompt	; address of message
	call WriteString		; write prompt
	call ReadInt			; read temperature
	mov value,eax			; save value
;*** load signed reference value and convert to 32 bits
	movsx eax,reference		; convert reference to 32 bits and load into eax
	cmp value,eax			; compare against value
;*** create a conditional structure to load message address
	
	jl else_branch			; jump to else_branch if value is less than reference
	jg else_branch2			; jump to else_branch2 if value is greater than reference
	mov edx, OFFSET equal	; otherwise load the address of string equal
	jmp end_if				; skip other code in conditional statement
else_branch:
	mov edx, OFFSET below	; load the address of string below
	jmp end_if				; skip other code in conditional statement
else_branch2:
	mov edx, OFFSET above   ; load the address of string below
end_if:

	call WriteString		; write eligability message
	call WaitMsg
	exit
main ENDP
END main
