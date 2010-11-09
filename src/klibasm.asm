GLOBAL  _read_msw, _lidt, _lgdt
GLOBAL	_remapPIC1
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug
GLOBAL	_write
GLOBAL	_read
GLOBAL	_invalidOpCode
GLOBAL	reloadSegments
GLOBAL	reload_CS
GLOBAL	rompe
GLOBAL _remapPIC1,_programPIT

EXTERN shell, writemem

SECTION .text

_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:

	sti			; habilita interrupciones por flag
	ret


_programPIT:				; Programa el PIT

	push	ebp
	mov	ebp, esp
	mov	ax, [ss:ebp+8]  	; ax = mascara de 16 bits

	mov	al, 36h
	out	43h, al
	;mov	ax,36b0h  5dc0h
	out	40h, al
	mov	al,ah
	out	40h, al
	
	mov	esp,ebp
	pop	ebp
	retn


_remapPIC1:			; Programa la Pic para que la 
				; IRQX interrumpa en otra pos de la IDT.
	push	ebp
	mov	ebp, esp

	mov	al, 11h
	out	20h, al
	mov	al, 20h
	out	21h, al
	mov	al, 04h
	out	21h, al
	mov	al, 01h
	out	21h, al

	mov	al, 011h
	out	0a0h, al
	mov	al, 0a0h
	out	0a1h, al
	mov	al, 02h
	out	0a1h, al
	mov	al, 01h
	out	0a1h, al

	mov	esp,ebp
	pop	ebp
	retn


_mascaraPIC1:				; Escribe mascara del PIC 1
	push	ebp
	mov	ebp, esp
	mov	ax, [ss:ebp+8]  	; ax = mascara de 16 bits
	out	21h,al
	pop	ebp
	retn

_mascaraPIC2:				; Escribe mascara del PIC 2
	push	ebp
	mov	ebp, esp
	mov	ax, [ss:ebp+8]  	; ax = mascara de 16 bits
	out	0A1h,al
	pop	ebp
	retn


_lidt:					; Carga el IDTR
	push	ebp
	mov	ebp, esp
	push	ebx
	mov	ebx, [ss: ebp + 6] 	; ds:bx = puntero a IDTR 
	rol	ebx,16		    	
	lidt	[ds: ebx]       	; carga IDTR
	pop	ebx
	pop	ebp
	retn


; Debug para el BOCHS, detiene la ejecución; Para continuar colocar 
; en el BOCHSDBG: set $eax=0
;


_debug:
	push	bp
	mov	bp, sp
	push	ax

vuelve:
	mov	ax, 1
	cmp	ax, 0
	jne	vuelve
	pop	ax
	pop	bp

	retn
 
       
retorna:
	jmp	$



SECTION .data

grubgdtr db	00,00,00,00,00,00
