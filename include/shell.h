/*********************************************
shell.h

*********************************************/

#ifndef _shell_
#define _shell_

#include "klibc.h"
#include "commands.h"
#include "stdio.h"

enum command_ret  {NO_CMD = -3, INVALID_CMD, VALID_CMD};

/* Ejecuta la shell. */
void shell(void);

/* Muestra el prompt. */
void prompt(void) ;

/* Recibe el comando del usuario guardando la informacion en la estructura
** referenciada por command_pointer. Devuelve un entero INVALID_CMD, VALID_CD,
** NO_CMD segun sea necesario. */
int getCommand(t_command* command_pointer);

/* Devuelve el indice del comando en la lista de comandos. Si el comando no
** existe, devuelve -1. */
int commandExists(char* cmd_name);

/* Ejecuta la funcion referenciada en el miembro function de la estructura
** referenciada por cmd_pointer. */
int exec_cmd(t_command* cmd_pointer);

/* Parsea la informacion de la string input y la guarda en la estructura
** referenciada por cmd_pointer. */
static void parseCommand(t_command* cmd_pointer, char * input) ;

/* Limpia la estructura usada para recibir los comandos. */
void cleanCommand(t_command * command);

#endif


