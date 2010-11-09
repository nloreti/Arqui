#include "../include/klibc.h"
#include "../include/kc.h"

extern int stack_anchor;

/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/
int tickpos2 = 640;

void k_clear_screen() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]='7';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
}

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}

void
programPic(void)
{
	_Cli();

	/* Se habilitan interrupciones de teclado y timer tick */
        _mascaraPIC1(0xF8); //0xFC
        _mascaraPIC2(0xEF); //0xFF

	_remapPIC1();

	_Sti();
}

void
programPit(int value){

	_programPIT(value);
}

size_t
sys_write(size_t fd, char* source, size_t count)
{
	int nWritten;

	if (fd == STDOUT)
	{
		writeToVideoBuffer(source, count);
		refreshScreen();
		return nWritten = count;
	}
	
}

size_t
sys_read(size_t fd, char* dest, size_t count)
{
	int n_read;
	if ( fd == STDIN )
	{
		n_read = readFromKb(dest, count);
		return n_read;
	}

	return 0;
}

void
returnFromException(void)
{
	int local_stack_anchor = stack_anchor;
	__asm__("mov %0, %%esp" : : "g" (local_stack_anchor));
	shell();
}

size_t
write(size_t fd, char* source, size_t count)
{
	int ret;
	
	__asm__ ( "movl %0, %%eax": : "g" (WRITE) );
	__asm__ ( "movl %0, %%ebx": : "g" (fd));
	__asm__ ( "movl %0, %%ecx": : "g" (source));
	__asm__ ( "movl %0, %%edx": : "g" (count));
	__asm__ ( "int $0x80");
	__asm__ ( "movl %%eax, %0": : "g" (ret) );
	
	return ret;
}

size_t
read(size_t fd, char* dest, size_t count)
{
	int ret ;
	
	__asm__ ( "movl %0, %%eax": : "g" (READ) ) ;
	__asm__ ( "movl %0, %%ebx": : "g" (fd)) ;
	__asm__ ( "movl %0, %%ecx": : "g" (dest)) ;
	__asm__ ( "movl %0, %%edx": : "g" (count)) ;
	__asm__ ( "int $0x80") ;
	__asm__ ( "movl %%eax, %0": : "g" (ret) ) ;
	
	return ret ;	
}

/*size_t
changeKeyboard(){

}*/

void
setStackAnchor(void)
{
	int local_stack_anchor;
	__asm__ ("mov %%esp, %0" : : "g" (local_stack_anchor) );
	stack_anchor = local_stack_anchor;
}
