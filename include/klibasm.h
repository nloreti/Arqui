#ifndef _klibasm_
#define _klibasm_

#include "../include/defs.h"

unsigned int    _read_msw();

void            _lidt (IDTR *idtr);

void		_programPIT(void);

void		_mascaraPIC1 (byte mascara);  /* Escribe mascara de PIC1 */
void		_mascaraPIC2 (byte mascara);  /* Escribe mascara de PIC2 */

void		_Cli(void);        /* Deshabilita interrupciones  */
void		_Sti(void);	 /* Habilita interrupciones */

void		_debug (void);


#endif




