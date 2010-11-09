GLOBAL  _int_20_hand, _int_21_hand, _int_80_hand, _int_32_hand
GLOBAL	_int_0_hand, _int_01_hand, _int_02_hand, _int_03_hand, _int_04_hand
GLOBAL	_int_05_hand, _int_06_hand, _int_07_hand, _int_08_hand, _int_09_hand
GLOBAL	_int_10_hand, _int_11_hand, _int_12_hand, _int_13_hand, _int_14_hand
GLOBAL	_int_16_hand

EXTERN	int_20, _Sti, int_21, sys_write, sys_read
EXTERN	int_0, int_01, int_02, int_03, int_04, int_05, int_06, int_07, int_08
EXTERN	int_09, int_10, int_11, int_12, int_13, int_14, int_16, int_32

SECTION .text

_int_0_hand:
	push	ds
	push	es                      ; Se salvan los registros
	pusha
	call	_Sti			
	call	int_0
	

_int_01_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	jmp	$
	call	int_01
	iret

_int_02_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_02
	

_int_03_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_03
	

_int_04_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_04
	

_int_05_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti  
	call	int_05
	

_int_06_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_06
	

_int_07_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_07
	

_int_08_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_08
	

_int_09_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_09
	

_int_10_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti  
	call	int_10
	

_int_11_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_11
	

_int_12_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_12
	
_int_13_hand:

	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_13
	

_int_14_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_14
	

_int_16_hand:
	push    ds
	push    es                      ; Se salvan los registros
	pusha  
	call	_Sti
	call	int_16
	

_int_20_hand:				; Handler de INT 8 (Timer tick)
	push    ds
	push    es                      ; Se salvan los registros
	pusha                           ; Carga de DS y ES con el valor del 
	mov     ax, 10h			; selector a utilizar.
	mov     ds, ax
	mov     es, ax                  
	call    int_20                 
	mov	al,20h			; Envio de EOI generico al PIC
	out	20h,al
	popa                            
	pop     es
	pop     ds
	iret

_int_21_hand:

	push	ds
	push	es                      ; Se salvan los registros
	pusha                           ; Carga de DS y ES con el valor del 
					; selector a utilizar.
	mov	ax, 10h
	mov	ds, ax
	mov	es, ax

	mov	eax, 00h
	in	al, 60h
	
	push	eax
	call	int_21
	pop	eax                

	mov	al,20h			; Envio de EOI generico al PIC

	out	20h,al
	popa                            
	pop	es
	pop	ds
	iret

_int_80_hand:
	push	ds
	push	es
	push	ebx
	push	ecx
	push	edx
	call	_Sti
	cmp	eax, 1			; Segun el parametro recibido en eax, 
					; se llama a la correspondiente
	jz	write			; system call.
	cmp	eax, 2						
	jz	read						
	jmp	endint

write:
	push	edx
	push	ecx
	push	ebx
	call	sys_write
	pop	ebx
	pop	ecx
	pop	edx
	jmp	endint

read:
	push	edx
	push	ecx
	push	ebx
	call	sys_read
	pop	ebx
	pop	ecx
	pop	edx
	jmp	endint

endint:
	pop	edx	                            
	pop	ecx
	pop	ebx
	pop	es
	pop	ds
	iret

_int_32_hand:
	;push    ds
	;push    es                      ; Se salvan los registros
	;pusha  
	;call	_Sti
	;call	int_32
	;popa
	;pop es
	;pop ds
	pop ax
	pop ax	
	iret

