#include "../include/shell.h"

#define MAX_COMMAND_LENGTH 256

extern t_cmd_entry* cmd_DB[MAX_COMMANDS];

void
shell(void)
{
	t_command command;
	while(1)
	{
		prompt();
		cleanCommand(&command);
		/* Se limpia la estructura antes de setearla. */
		switch(getCommand(&command))
		{
			case NO_CMD:
				break;
			case INVALID_CMD:
				puts(command.name);
				puts(": command not found\n");
				break;
			/* Si el comando es valido, se lo ejecuta. */
			case VALID_CMD:
				exec_cmd(&command);
				break;
		}		
	}
}

void
cleanCommand(t_command * command)
{
	int i;

	*(command->name) = '\0';
	command->argc = 0;
	for(i = 0; i<MAX_ARGS; i++)
		*(command->argv[i]) = '\0';
	command->function = NULL;
}

void
prompt(void)
{
	puts(getTty());
	puts("@Arqui:~$ ");
}

int
getCommand(t_command* cmd_pointer)
{
	char input[MAX_COMMAND_LENGTH];
	int cmd_index;

	/* Se toma el comando ingresado por el usuario. */
	gets(input, MAX_COMMAND_LENGTH);
	/* Se lo parsea y se deja la informacion en la estructura cmd. */
	parseCommand(cmd_pointer, input) ;
	
	/* Si solo fue presionado '\n' se omite el comando. */
	if(strcmp(cmd_pointer->name, "") == 0)
		return NO_CMD;
	
	/* Se verifica que el comando exista y lo identificamos en la
	** tabla de comandos. */
	if( (cmd_index = commandExists(cmd_pointer->name)) != INVALID_CMD)
		cmd_pointer->function = cmd_DB[cmd_index]->function;
	else
		return INVALID_CMD;

	return VALID_CMD;
}

int
commandExists(char* cmd_name)
{
	int cmd_index = 0;

	/* Se busca la posicion del comando en el vector de comandos. Si 
	este no se encuentra, se retorna como invalido. */
	while(cmd_DB[cmd_index] != NULL)
	{
		if( strcmp(cmd_DB[cmd_index]->name, cmd_name) == 0 )
			return cmd_index;
		else
			cmd_index++;
	}
	return INVALID_CMD;
}

int
exec_cmd(t_command* cmd_pointer)
{
	/* Se ejecuta la funcion correspondiente, con la cantidad de argumentos
	y el vector de argumentos */
	return cmd_pointer->function(cmd_pointer->argc, cmd_pointer->argv);
}


static void
parseCommand(t_command* cmd_pointer, char * input)
{
	
	int name_length = 0 ;
	int argc = 0 ;
	int arg_length ;
	
	/* Se omiten los espacios en blanco */
	while(isSpace(*input) && *input != '\0' ) 
		input++ ;

	/* Se levanta de input el string antes del primer espacio, siendo este
	** el nombre del comando  */	
	if  ( *input != '\0' )
	{
		while((!isSpace(*input) && *input != '\0')
								&& name_length < MAX_NAME_LENGTH-1) 		
			cmd_pointer->name[name_length++] = *input++ ;
	}
	cmd_pointer->name[name_length] = '\0' ;

	/* Se levantan los argumentos, los cuales se conforman de todos los
	** strings consiguientes al nombre del comando */	
	while ( *input != '\0' && argc < MAX_ARGS)
	{
		/* Se omiten los espacios en blanco */
		while(isSpace(*input) && *input != '\0' ) 
			input++ ;
	
		if  ( *input != '\0' )
		{
			arg_length = 0 ;
			while((!isSpace(*input) && *input != '\0') 
					&& arg_length < MAX_ARG_LENGTH-1 ) 		
			{
				cmd_pointer->argv[argc][arg_length++] = *input++ ;		
			}
			cmd_pointer->argv[argc++][arg_length] = '\0' ;
		}		
	}

	/* Se setea la cantidad de argumentos recibidos. No se toma en cuenta el
	** nombre del comando. */		
	cmd_pointer->argc = argc ;
}
