/**********************
 klibc.h
**********************/

#ifndef _klibc_
#define _klibc_

#include "defs.h"
#include "keyboard.h"
#include "stdio.h"
#include "video.h"
#include "shell.h"
#include "asm_ihandler.h"


/* write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t write(size_t fd, char* source, size_t count);

/* read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
size_t read(size_t fd, char* dest, size_t count);

void programPic(void);
void programPit(int);

/* Inicializa la entrada del IDT */
void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero);

/* Funcion que copia el contenido de la GDT que deja el GRUB, en una zona
** designada internamente */
void setup_GDT(void) ;

/* Funcion que almacena en 'dest' el segmento de GDT 'source' */
void setup_GDT_entry(DESCR_SEG * dest, DESCR_SEG source) ;

/* Funcion que obtiene el contenido del registro gdtr que deja el GRUB, y la
** almacena en una estructura tipo GDTR */
//GDTR getGrubGdtr(void) ;

/* Funcion que setea un nuevo segmento en la GDT */
//int setGdtSeg(unsigned int base, unsigned int limit, char tipo, char dpl, 
//int granularity, int comf_ed, int bitA, int bitS, int wr, int avl, int db);

/* Funcion que muestra en pantalla una cantidad de segmentos de la GDT dada
** por un rango entre 'GDTinit' y 'GDTend' */
//int infoGDT(int GDTinit, int GDTend);

/* Funcion que segun el file descriptor dado, escribe en este una cantidad 
** 'count' de valores tomados de 'source' */
size_t sys_write(size_t fd, char* source, size_t count);

/* Funcion que segun el file descriptor dado, lee de este una cantidad 'count'
** de valores almacenandolos en 'dest' */
size_t sys_read(size_t fd, char* dest, size_t count);

/* Guarda en una variable global el valor actual del registro ESP */
void setStackAnchor(void);

/* Funcion para retornar de rutinas de excepcion, restaurando el valor del
** registro ESP al original justo antes de ejecutar Shell() por primera vez. */
void returnFromException(void);

/* Funcion que dado un parametro que representa una cantidad en milisegundos
** y duerme al sistema por esa cantidad de tiempo. */
//int sleep(unsigned long int mseconds);

#endif
