/*********************************************
keyboard.h

************************************************/
#include "defs.h"

#ifndef _keyboard_
#define _keyboard_

#define KEYBOARD_MAXBUFFER 64
#define ON 1
#define OFF 0

#define FALSE 0
#define TRUE 1

#define ENG 0
#define ESP 1

#define LONGEST_SCANCODE 6

#define PGUP 5
#define PGDN 6

#define ACK 0xFA

#define ESC	0x02
#define L_CTRL 	0x1d
#define L_SHIFT	0x2a	
#define L_SHIFT_OUT 0xaa
#define R_SHIFT	0x36
#define R_SHIFT_OUT 0xb6
#define L_ALT	0x38
#define CAPS	0x3a
#define F1	0x3b
#define F2	0x3c
#define F3	0x3d
#define F4	0x3e
#define	F5	0x3f
#define F6	0x40
#define F7	0x41
#define F8	0x42
#define	F9	0x43
#define	F10	0x44
#define	F11	0x57
#define	F12	0x58
#define NUM	0x45
#define SCROLL	0x46
#define NDEF 	0x00
#define ACCENT	0x1A
#define R_CTRL	0x114
#define L_GUI	0x11f
#define R_GUI	0x127
#define ALT_GR	0x111
#define APPS	0x12f
#define	INSERT	0x170
#define HOME	0x16c
#define PG_UP	0x17d
#define DEL	0x171
#define END	0x169
#define	PG_DN	0x17a
#define UP_ARROW 	0x175
#define LEFT_ARROW	0x16b
#define	DOWN_ARROW	0x172
#define RIGHT_ARROW	0x174
#define KP_DIV	0x14A
#define	KP_EN	0x15a	

#define NDOT	0x53
#define N0	0x52
#define	N1	0x4F
#define	N2	0x50
#define	N3	0x51
#define	N4	0x4B
#define	N5	0x4C
#define	N6	0x4D
#define	N7	0x47
#define	N8	0x48
#define	N9	0x49
#define ESCAPED_PREFIX 0xe0

/* Buffer de teclado */

typedef struct {
	char ctrl_status;
	char shift_status;
	char caps_status;
	char alt_status;
	char num_status;
	char accent_status;
	char language;
} t_flags;


typedef struct {
	char* address;
	int index;
	int last;
	t_flags flags;
} t_kb_buffer;

/*enum specialKeys{ 	BKSP = -200, CAPSLCK, NUMLCK, SCLLCK, LSHFT, LCTRL, 
			LALT, RSHFT, RCTRL, RALT, DEL, TAB, OTHER } ;*/

/* Funcion que retarda al microprocesador para coordinacion con el buffer
** del teclado */
void kbWait(void);

void initKeyboardBuffer(void);

void keyBoardLanguage(void);

char * getLanguage();

/* Funcion que lee del buffer de teclado y guarda en dest una cantidad count
** scancodes procesados */
size_t readFromKb(char* dest, size_t count);

/* Funcion que devuelve 1 si el scancode recibido no es atomico, 0 si lo es. */
int hasNext(unsigned char* current, int current_index);

/* Funcion que setea flags de SHIFT, CAPS o CTRL segun el vector
** de scancodes recibidos  */
int setFlags(unsigned char* scancodes);

/* Funcion que devuelve 1 si el scancode cambia su valor si son presionadas
** las teclas SHFT o CAPS, 0 sino. */
int hasShift(char sc);

/* Funcion que convierte valores scancodes a ascii. Retorna -1 si el scancode 
** es no imprimible  */
char scancodeToAscii(unsigned char* scancodes);

#endif
