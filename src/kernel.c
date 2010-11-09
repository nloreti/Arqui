#include "../include/kernel.h"

DESCR_INT idt[0xFF];			/* IDT de 256 entradas*/
IDTR idtr;				/* IDTR */

int stack_anchor;
unsigned int timertick = 0;



/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{

        int i,num;

/* Borra la pantalla. */ 

	//k_clear_screen();
	
	/* Inicializacion de buffer de video. */
	initVideoBuffer();

	/* Inicializacion de la pantalla. */
	initScreen();
	
	/* Inicializacion de buffer de teclado. */
	initKeyboardBuffer();
//_debug();
	/* Se programa la PIC. */
	programPic();

	//programPit(13000);

	/* Seteo de la IDT. */
	setup_IDT();

	/* Pantalla inicial. */
	showSplashScreen() ;

	/* Se guarda una referencia al STACK para retorno de excepciones. */
	//setStackAnchor();

	while(1)
	{
		shell();
	}	
	
}

setup_IDT(void)
{

	setup_IDT_entry (&idt[0x20], 0x08, (dword)&_int_20_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x21], 0x08, (dword)&_int_21_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x0a4], 0x08, (dword)&_int_32_hand, ACS_INT, 0);
	
	setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80_hand, ACS_INT, 0);
		
	

	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE EXCEPCIONES */
	setup_IDT_entry (&idt[0x00], 0x08, (dword)&_int_0_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x01], 0x08, (dword)&_int_01_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x02], 0x08, (dword)&_int_02_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x03], 0x08, (dword)&_int_03_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x04], 0x08, (dword)&_int_04_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x05], 0x08, (dword)&_int_05_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x06], 0x08, (dword)&_int_06_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x07], 0x08, (dword)&_int_07_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x0A], 0x08, (dword)&_int_10_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x0B], 0x08, (dword)&_int_11_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x0C], 0x08, (dword)&_int_12_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x0D], 0x08, (dword)&_int_13_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x0E], 0x08, (dword)&_int_14_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x10], 0x08, (dword)&_int_16_hand, ACS_INT, 0);

	/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

}

