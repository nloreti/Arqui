/*********************************************
	commands.h

*********************************************/

#include "../include/shell.h"
#include "../include/klibc.h"

#ifndef _commands_
#define _commands_

//#include "../include/animation.h"

#define HELP_ECHO \
	"echo: echo [arg ...]\n"\
	"\tDisplays the arguments entered.\n"
		
#define HELP_HELP \
	"help: help [command]\n"\
	"\tDisplays information about available commands."
			
#define HELP_INFOGDT \
	"infogdt: infogdt [[entry#] | [lowerLimit higherLimit]]\n"\
	"\tDisplays information about the Global Descriptor Table.\n\n"\
	"\t- If no arguments are entered, the program will show all the\n"\
	"\t  entries of the GDT. \n"\
	"\t- If 1 argument is entered, the entry at that number will be showed.\n"\
	"\t- If 2 arguments are entered, the entries within the range \n"\
	"\t  [lowerLimit-higherLimit] are showed."		
					
#define HELP_SETGDT \
	"setgdt: [base limit sType dpl]\n"\
	"\tAllows the user to load a segment descriptor in the Global Descriptor \n"\
	"\tTable.\n"\
	"\t- If 0 arguments are entered, the program wizard will ask for\n"\
	"\t  parameters.\n"\
    "\t- If 4 arguments are entered, they will be interpreted as base, limit,\n"\
	"\t  segment type and access permissions respectively in hexadecimal base.\n" 

#define HELP_ZERODIVIDE \
	"zerodivide:\n"\
	"\tThrows zero divide exception.\n"
	 
#define HELP_SEGFAULT \
	"segfault:\n"\
	"\tThrows segmentation fault exception.\n"
	
#define HELP_INVALIDOPCODE\
	"invalidopcode:\n"\
	"\tThrows invalid opcode exception.\n"
	 
#define HELP_SLEEP \
	"sleep: sleep SECONDS\n"\
	"\tDelay for a specified amount of seconds.\n"

#define HELP_ANIMATION \
	"animation: animation\n"\
	"\tShows an ascii art animation by  Joan Stark.\n"
	
#define	HELP_CLEAR \
	"clear: clear\n"\
	"\tClears the screen.\n"

#define HELP_LS \
	"ls: ls\n"\
	"\tHome sweet home, looks like Linux.\n"

#define HELP_WRITEMEM \
	"writemem: writemem\n"\
	"\tWrites 5 lines with the letter 'X' to the address 0xB8000."

#define HELP_TTY \
	"ttys: ttys\n"\
	"\tAsk for a number and Change TTYs to that number if exist.\n"

	
#define HELP_PL \
	"pl: pl [csSegIndex dsSegIndex csDPL dsDPL]\n"\
	"\tSets cs and ds with the GDT descriptors at the index csSegIndex and\n"\
	"\tdsSegIndex respectively.\n"\
	"\t- If 0 arguments are entered, the program wizard will ask for\n"\
	"\t  parameters.\n"\
    "\t- If 4 arguments are entered, they will be interpreted as csSegIndex,\n"\
    "\t  dsSegIndex, csDPL and dsDPL."

#define MAX_ARGS 40
#define MAX_ARG_LENGTH 20
#define MAX_NAME_LENGTH 15
#define HELP_LENGTH 500
#define MAX_COMMANDS 20 

typedef struct{
	char name[MAX_NAME_LENGTH];
	int (*function)();
	char help[HELP_LENGTH];
} t_cmd_entry;

typedef struct{
	char name[MAX_NAME_LENGTH];
	int argc;
	char argv[MAX_ARGS][MAX_ARG_LENGTH];
	int (*function)();
} t_command;

/* Funcion que imprime argumentos de tipo string en pantalla. */
int echo(int argc, char arguments[MAX_ARGS][MAX_ARG_LENGTH]);

/* Funcion simula un ls en el directorio /root de linux. */
int ls(int argc, char arguments[MAX_ARGS][MAX_ARG_LENGTH]);

/* Funcion que provee ayuda general sobre manejo de la shell, o
** ayuda sobre un comando en particular si se lo pasa como argumento. */
int help(int argc, char arguments[MAX_ARGS][MAX_ARG_LENGTH]);

/* Funcion que valida los parametros para setear un nuevo segmento en la GDT, 
** tanto para los que reciben por la linea de comandos, como en el wizard. */
int wrapperSetGdtSeg(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

/* Funcion que valida los parametros para desplegar informacion de la GDT. */
int wrapperInfoGDT(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

/* Funcion que ejecuta rutina de prueba para la excepcion "Zero Divide". */
int zeroDivide(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

/* Funcion que ejecuta rutina de prueba para la excepcion "General Protection". */
int segmentationFault(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

/* Wrapper para funcion que ejecuta rutina de prueba para la
** excepcion "Invalid Opcode". */
int wrapperinvalidOpCode(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

/* Escribe una sucesion finita de caracteres 'X' en la direccion de memoria 
** 0xB8000*/
int writemem(int arc, char argv[MAX_ARGS][MAX_ARG_LENGTH]) ;

/* Recibe index de descriptores de la GDT a los que apuntaran los registros CS
** DS, y los permisos correspondientes a esos descriptores. Ejecuta la funcion
** writemem. */
int checkdpl(int arc, char argv[MAX_ARGS][MAX_ARG_LENGTH]) ;

/* Limpia la pantalla y posiciona el prompt y el cursor en la esquina sueperior
** izquierda de la misma. */
int clear(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

/* Muestra en pantalla una animacion ASCII hecha por Joan Stark. */
int animation(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

/* Llama a la funcion sleep de la libreria klibc. */
int wrapperSleep(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

int ttys(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

#endif
