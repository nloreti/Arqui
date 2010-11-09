/*********************************************
commands.c

*********************************************/


#include "../include/commands.h"

extern unsigned long int timertick;

/* TODO: Sacar el writemem, el segfault, poner un comando para cambiar de teclado, comando para cambiar de tt's */
/* Se setean todos los comandos */
t_cmd_entry cmd1 = { "help", help, HELP_HELP };
t_cmd_entry cmd2 = { "zerodivide", zeroDivide, HELP_ZERODIVIDE};
t_cmd_entry cmd3 = { "segfault", segmentationFault, HELP_SEGFAULT};
t_cmd_entry cmd4 = { "echo", echo, HELP_ECHO };
t_cmd_entry cmd5 = { "writemem", writemem, HELP_WRITEMEM };
t_cmd_entry cmd6 = { "ls", ls, HELP_LS };
t_cmd_entry cmd7 = { "clear", clear, HELP_CLEAR };
t_cmd_entry cmd8 = { "tty", ttys, HELP_TTY };

//t_cmd_entry cmd10 = { "sleep", wrapperSleep, HELP_SLEEP };
//t_cmd_entry cmd6 = { "pl", checkdpl, HELP_PL };
//t_cmd_entry cmd4 = { "invalidopcode", wrapperinvalidOpCode, HELP_INVALIDOPCODE };

/* Se habilitan los comandos guardandolos en el vector de comandos */
t_cmd_entry* cmd_DB[MAX_COMMANDS] = { &cmd1, &cmd2, &cmd3, &cmd4, &cmd5,
	&cmd6, &cmd7, &cmd8, NULL };

extern t_gdt gdt_struct;

int
ttys(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	if(argc == 0 || argc > 1){
		printf("Use help [command] for more information\n");	
	}else{
		switch(argv[0][0]){
			case '0':
			case '1':
			case '2':
			case '3':
				
				changeTty(argv[0][0]);
				break;
			default: printf("Invaliad tty number\n");
		} 
	}
}

int
help(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	int i = 0;
	
	/* Se valida segun cantidad de argumentos.  */
	if ( argc == 0 )
	{
		printf("Available commands: \n");
		while ( cmd_DB[i] != NULL )
			printf("    -- %s \n", cmd_DB[i++]->name);
		printf("Use 'help [command]' for more information.\n");
	}
	else if ( argc == 1 )
	{
		if((i=commandExists(argv[0])) != INVALID_CMD)
			printf("%s\n", cmd_DB[i]->help);
		else
			printf("help: command \"%s\" not found\n", argv[0]);		
	}
	else if ( argc > 1 )
	{
		printf("help: too many arguments \n");
		printf("Use: help [command] \n");
	}

	return 1;
}

int
echo(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	int i;
	
	for ( i = 0 ; i < argc ; i++ )
	{
		puts(argv[i]);
		putc(' ');	
	}
	putc('\n');

	return 1;
}

int
ls(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	int i;
	putc(BLUE);
	printf("bin     dev     lib     opt     srbin    user\n");	
	printf("boot    etc     media   proc    sys      vmlinuz\n");
	printf("cdrom   home    mnt     root    tmp\n");	
	putc(WHITE_TXT);
	return 1;
}






int
zeroDivide(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	int aux = 2, i;
	
	/* Se crea un ciclo para dividir necesariamente por cero */
	for(i = -1; i < 2 ; i++)
		aux /= i;

	return 0;
}

int
segmentationFault(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	/* Se llama a una interrupcion que no existe
	** para generar Segmentation Fault */

	__asm__("int $0x25");

	return 0;
}

/*int
wrapperinvalidOpCode(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	_invalidOpCode();

	return 0;
}*/

int
writemem(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	char * video = (char *)0xB8000;
	int i;
	
	/* Escribe 'X' en las primeras 5 lineas del video. */
	for ( i = 0 ; i < LINE_SIZE*5 ; i++ )
		video[i++] = 'X';

	returnFromException();

	return 0;	
}
/*int
checkdpl(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	int	dpl_cs, dpl_ds, cs, ds;
	int badarg = FALSE;
	char * input;

	if(argc == 4)
	{
		cs = atoi(argv[0]);
		ds = atoi(argv[1]);
		dpl_cs = atoi(argv[2]);
		dpl_ds = atoi(argv[3]);	
	}
	else if (argc == 0)
	{
			printf("Insert Code Segment Selector: ");
			gets(input,MAX_ARG_LENGTH);
			cs = atoi(input);
			printf("Insert Data Segment Selector: ");
			gets(input,MAX_ARG_LENGTH);
			ds = atoi(input);
			printf("Insert DPL for Code segment: ");
			gets(input,MAX_ARG_LENGTH);
			dpl_cs = atoi(input);
			printf("Insert DPL for Data segment: ");
			gets(input,MAX_ARG_LENGTH);
			dpl_ds = atoi(input);
	}
	else
		badarg = TRUE;

	if(cs < 1 || cs > gdt_struct.last_seg || ds < 1 || ds > gdt_struct.last_seg
		 || dpl_cs < 0 || dpl_cs > 3  || dpl_ds < 0 || dpl_ds > 3 || badarg)
	{
		printf("Invalid arguments\n");
				
	}
	else
	{
		cs = cs * 8 + dpl_cs;
		ds = ds * 8 + dpl_ds;

		rompe(ds,cs);
	}

	return 1;	
}*/

int
clear(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	/* Imprime en pantalla el caracter de escape que al interpretarse limpia
	** la pantalla. */
	
	putc(CLRSCR);

	return 0;
}

/*int
animation(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{
	char * frames[] = { FRAME1, FRAME2, FRAME3, FRAME4, FRAME5, FRAME6,
						FRAME7, FRAME8, FRAME9, FRAME10, FRAME11, FRAME12,
						FRAME13, FRAME14, FRAME15, FRAME16, FRAME17, FRAME18,
						FRAME19, FRAME20, FRAME21, FRAME22, FRAME23, FRAME24,
						FRAME25, FRAME26, FRAME27, FRAME28, FRAME29, FRAME30,
						FRAME31, FRAME32} ; 

	int i, size ;
	
	size = sizeof(frames)/sizeof(frames[0]) ;
	
	clear(0, (char (*)[20])0);
	putc(GREEN);
	
	for ( i = 0 ; i < size ; i++ )
	{
		printf("%s \n", frames[i]);
		sleep(250);
		clear(0, (char (*)[20])0);
	} 
	putc(WHITE_TXT);

	return 0 ;					
}*/

/*int
wrapperSleep(int argc, char argv[MAX_ARGS][MAX_ARG_LENGTH])
{

	int seconds;

	if ( argc != 1 )
	{
		printf("Invalid amount of arguments.\n");
		return 0;
	}
	if ( !isIntString(argv[0]) )
	{
		printf("The operand must be an integer.\n");
		return 0;
	}
	
	seconds = atoi(argv[0]);

	sleep(seconds*1000);
			
	return 1;
}*/
