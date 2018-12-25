TITLE L03 - Subroutine Calls & IO

; Ben Sebring
; 14158
; CPSC 232 Introduction to Assembler Programming
; Prof. James W. Emert
; Goal: Demonstrate the ability to call Irvine routines and perform I/O.
; Method: Prompt for the user's weight. Enter the weight and print a message containing the weight.
;
;	The text and number of the message must be displayed on the same line.
;	All values must be unsigned integers.
;	The Irvine routine CRLF may not be used.


INCLUDE Irvine32.inc
.data

;*** Declare an unsigned, integer variable for the value
weight	DWORD	?

;*** Declare the prompt and message parts
prompt	BYTE	"Enter your weight: ", 0
message	BYTE	"Weight: ", 0
endLn	BYTE	0dh, 0ah, 0 ;End of line part

.code
main PROC
	;*** print the prompt for the user's weight in pounds
	mov	edx, OFFSET prompt
	call WriteString

	;*** read user's weight and store it in a variable
	call ReadDec
	mov	weight, eax

	;*** print first part of message
	mov	edx, OFFSET message
	call WriteString

	;*** print user's weight
	mov	eax, weight
	call WriteDec

	;*** optionally you may print additional text
	;*** print end of line
	mov edx, OFFSET endLn
	call WriteString

	;*** NOTE: DumpRegs is not permitted in this program.
	call WaitMsg			; wait for user to read results
	exit
main ENDP
END main