#include "../include/keyboard.h"


t_kb_buffer keyboard_buffer;
char k_buffer[KEYBOARD_MAXBUFFER];

typedef struct {
	char * firstByteMap;
	char * shiftByteMap;
} t_keyboard;


/* Tabla de referencia de valores ascii para cada scancode ingles*/
	char minus_eng[] = 
	{NDEF,ESC,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t','q',
 	'w','e','r','t','y','u','i','o','p','[',']','\n',L_CTRL,'a','s','d','f',
 	'g','h','j','k','l',';','\'','B',L_SHIFT,'\\','z','x','c','v','b','n',
 	'm',',','.','/',R_SHIFT,'*',L_ALT,' ',CAPS,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,
	NDEF,NUM,SCROLL,N7,N8,N9,'-',N4,N5,N6,'+',N1,N2,N3,N0,NDOT,NDEF,NDEF,'<',
 	NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,
	NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,
	NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF };

	/* Tabla de referencia de valores ascii para cada scancode, segun flags
	** CAPS y SHIFT en ingles*/
	char mayus_eng[] = 
	{NDEF,ESC,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q',
 	'W','E','R','T','Y','U','I','O','P','{','}','\n',L_CTRL,'A','S','D','F',
	'G','H','J','K','L',':', '\'',NDEF,L_SHIFT,'|','Z','X','C','V','B','N',
 	'M','<','>','?',R_SHIFT,'G',L_ALT,' ', CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,
 	F10,NUM,SCROLL,N7,N8,N9,'-',N4,N5,N6,'+',N1,N2,N3,N0,NDOT,NDEF,NDEF,'>',
 	F11,F12,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,
	NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF, 	
	NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF};

	/* Tabla de referencia de valores ascii para cada scancode */
	char minus_esp[] = /*{NDEF,0xb3,'1','2','3','4','5','6','7','8','9','0','\'',0xa8,'\b','\t','q','w','e','r','t','y','u','i','o','p','{','}','\n',NDEF,'a','s','d','f','g','h','j','k','l',164,'´','+',0,0xb3,'z','x','c','v','b','n','m',',','.','-','\\','.',56,' ',58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,'<'};*/

	{NDEF,ESC,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t','q',
 	'w','e','r','t','y','u','i','o','p','[',']','\n',L_CTRL,'a','s','d','f',
 	'g','h','j','k','l',164,'\'',NDEF,L_SHIFT,'\\','z','x','c','v','b','n',
 	'm',',','.','/',R_SHIFT,'*',L_ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,
	F10,NUM,SCROLL,N7,N8,N9,'-',N4,N5,N6,'+',N1,N2,N3,N0,NDOT,NDEF,NDEF,'<',
 	F11,F12,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,
	NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,
	NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF };

	/* Tabla de referencia de valores ascii para cada scancode, segun flags
	** CAPS y SHFT */
	char mayus_esp[] = 
	{NDEF,ESC,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q',
 	'W','E','R','T','Y','U','I','O','P','{','}','\n',L_CTRL,'A','S','D','F',
	'G','H','J','K','L',165, '\'',NDEF,L_SHIFT,'|','Z','X','C','V','B','N',
 	'M','<','>','?',R_SHIFT,'*',L_ALT,' ', CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,
 	F10,NUM,SCROLL,N7,N8,N9,'-',N4,N5,N6,'+',N1,N2,N3,N0,NDOT,NDEF,NDEF,'>',
 	F11,F12,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,
	NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF, 	
	NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF,NDEF};


t_keyboard keyboardMap[2];

/* Se inicializa el buffer de teclado */
void
initKeyboardBuffer(void)
{
	keyboard_buffer.address = k_buffer;
	keyboard_buffer.index = 0;
	keyboard_buffer.last = 0;
	keyboard_buffer.flags.ctrl_status = OFF;
	keyboard_buffer.flags.shift_status = OFF;
	keyboard_buffer.flags.alt_status = OFF;
	keyboard_buffer.flags.caps_status = OFF;
	keyboard_buffer.flags.num_status = OFF;
	keyboard_buffer.flags.accent_status = OFF;
	keyboard_buffer.flags.language = ENG;

	keyboardMap[ENG].firstByteMap = minus_eng;
	keyboardMap[ENG].shiftByteMap = mayus_eng;
	keyboardMap[ESP].firstByteMap = minus_esp;
	keyboardMap[ESP].shiftByteMap = mayus_esp;

}


int
setFlags(unsigned char* scancodes)
{

	int modify = FALSE;

	if(scancodes[0] == R_SHIFT || scancodes[0] == L_SHIFT){
		keyboard_buffer.flags.shift_status = ON;
		modify = TRUE;	
	}
	else if(scancodes[0] == R_SHIFT_OUT  || scancodes[0] == L_SHIFT_OUT ){
		keyboard_buffer.flags.shift_status = OFF;
		modify = TRUE;	
	}else if( scancodes[0] == CAPS ){
		keyboard_buffer.flags.caps_status = !keyboard_buffer.flags.caps_status;
		modify = TRUE;
	}else if( (scancodes[0] == ESCAPED_PREFIX && scancodes[1] != 0x9D) || scancodes[0] == 0x9D ){
		keyboard_buffer.flags.ctrl_status = OFF;
		modify = TRUE;
	}else if( (scancodes[0] == ESCAPED_PREFIX && scancodes[1] != L_CTRL) || scancodes[0] == L_CTRL ){
		keyboard_buffer.flags.ctrl_status = ON;
		modify = TRUE;
	}

	

	return modify;
}

void
keyBoardLanguage(void){

		if( keyboard_buffer.flags.shift_status == ON && 
			keyboard_buffer.flags.ctrl_status == ON && 
				keyboard_buffer.flags.caps_status == ON){
		if ( keyboard_buffer.flags.language == ENG )
			keyboard_buffer.flags.language = ESP;
		else
			keyboard_buffer.flags.language = ENG;	
		}
}

int
hasNext(unsigned char* current, int current_index)
{
	unsigned char lsc = current[current_index];
	int hasNext = FALSE;
	
	switch(current_index)
	{
		case 0: if( lsc == 0xE0 || lsc == 0xE1 )
				hasNext = TRUE;
				break;
		case 1: if( lsc == 0x24 || lsc == 0xB7 || lsc == 0x1D )
				hasNext = TRUE;
				break;
		case 2: if( lsc == 0xE0 || lsc == 0x45)
				hasNext = TRUE;
				break;
		case 3: if( lsc == 0xE1 )
				hasNext = TRUE;
				break;			
		case 4: if( lsc == 0x9D )
				hasNext = TRUE;
	}

	return hasNext;
}

char
scancodeToAscii(unsigned char* scancodes)
{
	char ret;

	/* Se setean las flags segun el scancode sea CTRL, CAPS, o SHFT */
	int modifyflag = setFlags(scancodes);
	
	/* Cambia el idioma del teclado de ser necesario, revisando el estado de los flags*/	
	keyBoardLanguage();

	if( scancodes[0] < 100 && ( modifyflag != TRUE ) )
	{
		if( keyboard_buffer.flags.language == ENG )		
			ret = keyboardMap[ENG].firstByteMap[scancodes[0]];
		else
			ret = keyboardMap[ESP].firstByteMap[scancodes[0]];
		/* Si el scancode corresponde a un caracter imprimible, 
		** se valida con los flags de SHFT y CAPS de que tabla 
		** levantar el caracter */
		if ( ret > 0 )
		{
			if(hasShift(ret))
				if( ((keyboard_buffer.flags.shift_status ^ keyboard_buffer.flags.caps_status) && 
					isLower(ret)) || (keyboard_buffer.flags.shift_status && !isLower(ret))){
					if( keyboard_buffer.flags.language == ENG )					
						return keyboardMap[ENG].shiftByteMap[scancodes[0]];
					else
						return keyboardMap[ESP].shiftByteMap[scancodes[0]];
				}
			return ret;
		
		}
	}
	else if(scancodes[0] == 0xE0 && scancodes[1] == 0x49)
		return PGUP;
	else if(scancodes[0] == 0xE0 && scancodes[1] == 0x51)
		return PGDN;
	return -1 ;
}

int
hasShift(char sc)
{
	if( isLower(sc) || isDigit(sc) || sc == '-' || sc == '=' || sc == '[' ||
		sc == ']' || sc == '\'' || sc == '`' ||	sc == '\\' ||
		sc == ',' || sc ==  '.' || sc ==  '/' || sc == ';' )
		return TRUE;		
}

void
enqueueKbBuffer(char sc)
{
	int i ;
	static int currentindex = 0  ;
	/* Vector donde se almacena el scancode completo. */
	static unsigned char fullsc[LONGEST_SCANCODE] ; 

	fullsc[currentindex] = sc ;
	
	if ( hasNext(fullsc, currentindex) == FALSE )
	{
		if ( keyboard_buffer.last + currentindex + 1 != keyboard_buffer.index )		
		{
			for ( i = 0 ; i < currentindex + 1 ; i++ )
			{
				if ( keyboard_buffer.last == KEYBOARD_MAXBUFFER )
					keyboard_buffer.last = 0 ;
				keyboard_buffer.address[keyboard_buffer.last++] = fullsc[i];
			}
			currentindex = 0 ;
		}
	}
	else
		currentindex++;
	//int n = readFromKb(k_buffer, LONGEST_SCANCODE);
	//write(STDOUT,k_buffer,n);
}

size_t
readFromKb(char* dest, size_t count)
{
	int i, n_read ;
	signed char byte_read ;
	/* Vector para almacenar scancodes. */
	unsigned char current[LONGEST_SCANCODE] = {0,0,0,0,0,0};
	int current_index = 0;
	/* En n_read se guarda la cantidad de caracteres leidos. */
	n_read = 0 ;
	if(dest == 0)
		return -1;

	/* Se levantan scancodes del buffer mientras la cantidad leida sea
	** menor al argumento 'count', y aun queden scancodes en el buffer. */		
	while (n_read < count && keyboard_buffer.index != keyboard_buffer.last)
	{
		if (keyboard_buffer.index == KEYBOARD_MAXBUFFER)
			keyboard_buffer.index = 0;

		current[current_index] = keyboard_buffer.address[keyboard_buffer.index++];
		
		/* Si el scancode no esta completo, se levanta el siguiente. */	
		if(hasNext(current, current_index) == 1)
		{
			current_index++;
		}
		else
		{	/* Se obtiene el valor ascii del scancode. */
			byte_read = scancodeToAscii(current) ;
			/* Si el mismo es imprimible, se lo guarda en 'dest'. */
			if( byte_read >= 0)
				dest[n_read++] = byte_read ;
				
			/* Se limpia el vector que almacenara un nuevo scancode. */
			for( i = 0; i < 6 ; i++)
				current[i]=0;
		}
	}
	return n_read ;
}


char *
getLanguage(void){
	char * resp;
	if( keyboard_buffer.flags.language == ESP){
		resp = "Esp";
	}else{
		resp = "Eng";
	}

	return resp;
}
