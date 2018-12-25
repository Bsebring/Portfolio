TITLE Bit Manipulation Homework

; Ben Sebring
; Section	14158 
; CPSC 232 Introduction to Assembler Programming 
; Prof. James W. Emert
; Assignment: Homework 5
; Description: create calcCRC, verify calcCRC, test for single bit error, test for burst error

INCLUDE Irvine32.inc
.data
string			BYTE		"Computer",0,0,0			
crc_return		DWORD		0							

.code
main PROC
	push OFFSET crc_return					; blank crc_return
	push SIZEOF string						; size of string
	push OFFSET string						; "Computer"
	call calcCRC							; call subroutine
	mov eax, crc_return						; move crc_return to eax
	call WriteHex							; display hex number
	call Crlf								; carriage return and line feed

	shl eax, 11								; Shifting the crc_return by 11 to left align it
	mov edi, OFFSET string + 8				; Set destination to end of string
	cld										; clear direction flag
	mov ecx, 3								; mov 3 into ecx for loop counter
big_endian_loop:							; loop to store crc_return into the string in big endian style
	rol eax, 8								; rotate the eax register by 8 bits to the left
	stosb									; store one signed byte into the al register
	loop big_endian_loop					; loop if ecx not equal to zero
	
				
		
	push OFFSET crc_return					; crc_return
	push SIZEOF string						; size of string
	push OFFSET string						; "Computer"
	call calcCRC							; call subroutine
	mov eax, crc_return						; move crc_return to eax
	call WriteHex							; display hex number
	call Crlf								; carriage return and line feed

	mov al, string + 0						; set up single bit error
	btc ax, 0
	mov string+0, al						; finish up single bit error

	push OFFSET crc_return					; crc_return
	push SIZEOF string						; size of string
	push OFFSET string						; "Computer"
	call calcCRC							; call subroutine
	mov eax, crc_return						; move crc_return to eax
	call WriteHex							; display hex number
	call Crlf								; carriage return and line feed

	mov string + 0, 73						; set up burst error
	mov string + 1, 68					
	mov string + 2, 69					
	mov string + 3, 74						; finish up burst error

	push OFFSET crc_return					; crc_return
	push SIZEOF string						; size of string
	push OFFSET string						; "Computer"
	call calcCRC							; call subroutine
	mov eax, crc_return						; move crc_return to eax
	call WriteHex							; display hex number
	call Crlf								; carriage return and line feed

	call WaitMsg				
	exit
main ENDP
.data
poly			DWORD			00302899h

.code
calcCRC PROC
PARAMS	= (5+1)*TYPE DWORD 
NPARAMS = 3
sub_string = PARAMS + 0*TYPE DWORD
bytes = PARAMS + 1*TYPE DWORD
checksum = PARAMS + 2*TYPE DWORD

	push eax						; Save working flags and registers
	push ebx
	push ecx
	push edx
	pushfd

	mov edx, 0						; move 0 to edx
	mov eax, 0						; move 0 to edx
	mov ecx, bytes[esp]				; move number of bytes to ecx
	mov esi, sub_string[esp]		
							  
outer_For_Loop:												  
	lodsb							; load byte 
	mov ebx, eax					; save to ebx
	jmp last_byte_check				; jump to last_byte_check loop
									  
	last_byte_check:								  						  
		cmp ecx, 1						; compare ecx to 1
		jne  continue					; if ecx != 1 jump to continue loop
		push ecx						; save counter
		mov ecx, 5						; move 5 to ecx
		jmp inner_For_Loop						; jump to inner_For_Loop loop

	continue:							
		push ecx						; save counter
		mov ecx, 8						; move 8 to ecx
		jmp inner_For_Loop				; jump to inner_For_Loop loop

	inner_For_Loop:													  
		shl bl, 1						; shift bl by 1
		rcl edx, 1						; rotate carry left

		do_Xor:								
			bt edx, 21			 			; copy bit 21 into carry flag and clear bit 21
			jnc noXOR						; jump noXOR loop 
			xor edx, poly					; xor with poly

		noXOR:								
			loop inner_For_Loop				; jump back to inner_For_Loop loop
			pop ecx							; pop ecx to resume outer loop counter						  
			loop outer_For_Loop				; jump back to outer_For_Loop loop

stop:
	mov ebx, checksum[esp]			; load checksum
	mov DWORD PTR [ebx], edx		
													  
	popfd
	pop edx
	pop ecx
	pop ebx
	pop eax											  
													  
	ret NPARAMS*TYPE DWORD							

calcCRC ENDP
end MAIN