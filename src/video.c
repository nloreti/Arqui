/***********************************************
video.c

manejo de video
************************************************/

#include "../include/video.h"

/* Macro util para insertar un blanco en una direccion. */
#define INSERTBLANK(index)\
				 	vd_buffer.address[(index) % VD_BUFF_SIZE ] = ' ' ;\
					vd_buffer.address[((index)+1) % VD_BUFF_SIZE ] = WHITE_TXT

t_tty tty;
t_screen screen ;
t_video_buffer vd_buffer;
char v_buffer[VD_BUFF_SIZE];


void
initVideoBuffer(void)
{
	
	int i, j;
	j = 0;

	tty.current = 0;
	for( j = 0; j < N_TTY; j++ ){
		tty.ttys[j].address = v_buffer;
	
		/* Indice donde se mapea el principio de la pantalla en el buffer
		** de video. */
		tty.ttys[j].base = 0;
	
		/* Indice donde se escribe en el buffer de video. */
		tty.ttys[j].index = 0;

		/* Indice que se utiliza para mover la base al hacer un scroll. */ 
		tty.ttys[j].scroll_base = 0;

		/* Flag que indica si se necesitan nuevas lineas. */
		tty.ttys[j].line_feed = FALSE;
	
		/* Flag utilizada para el manejo del scroll up/down. Si first_lap = TRUE,
		** entonces el buffer circular todavia no llego a recorrer una vuelta. */ 
		tty.ttys[j].first_lap = TRUE;

		/* Flags que indican si se leyeron caracteres de PGUP/PGDW y CLRSCR */	
		tty.ttys[j].scroll_flag = FALSE;
		tty.ttys[j].clr_flag = FALSE;

		/* Se limpian los primeros SCREEN_SIZE bytes del buffer para poder
		** inicializar la pantalla.
		*/
		for ( i = 0 ; i < SCREEN_SIZE ; i++)
		{
			INSERTBLANK(tty.ttys[j].index + i);
			i++ ;
		}
	}
}

void
initScreen(void)
{
	screen.address = (char *)SCREEN_ADDRESS ;
	screen.offset = 0 ;
	/* Atributo de color seteado en blanco sobre negro por default. */
	screen.color_att = WHITE_TXT;
	/* Se limpia la pantalla al refrescarla con los primeros SCREEN_SIZE bytes
	** del buffer de video. */
	refreshAll() ;
}


void
changeTty(char number){
	int ttynumber = (int)(number-'0');
	printf("%d\n",ttynumber);
	tty.current = ttynumber;
	writeToVideoBuffer(tty.ttys[tty.current].address, SCREEN_SIZE);
	//refreshAll();
	//clearScreen();
	//lrefreshScreen();
	
}

void
writeToVideoBuffer(char * str, int count)
{
	int i ;

	/* Se intera sobre los caracteres de la cadena str. */
	for(i = 0; i < count ; i++)
	{
		switch((int) str[i])
		{
			case '\b':
				insertBackspace() ;
				break;
			case '\n':
				insertNewline() ;
				break;
			case '\t':
				insertTab() ;
				break;
			case PGUP:
				insertPageup();
				tty.ttys[tty.current].scroll_flag = TRUE;
				break;
			case PGDN:
				insertPagedown();
				tty.ttys[tty.current].scroll_flag = TRUE;
				break;
			case CLRSCR:
				clearScreen();
				tty.ttys[tty.current].clr_flag = TRUE;
				break;
			case GREEN: case BLUE: case RED: case WHITE_TXT:
				screen.color_att = str[i] ;
				break;
			default:
				insertCharacter(str[i]);
				break;
		}
	}
	
	
	if(tty.ttys[tty.current].index > VD_BUFF_SIZE)
	{
		/* Si el indice es mayor que el tamaño de buffer, entonces el buffer
		** ya dio una vuelta. */
		tty.ttys[tty.current].first_lap = FALSE;
		tty.ttys[tty.current].index %= VD_BUFF_SIZE; /* Reajuste de index. */
	}
	if(tty.ttys[tty.current].base > VD_BUFF_SIZE)
		tty.ttys[tty.current].base %= VD_BUFF_SIZE; /* Se reajusta la base. */		
		
	
	
	if( (tty.ttys[tty.current].line_feed = needsLineFeed()) == TRUE )
		insertLineFeed() ; /* Agrega lineas nuevas necesarias. */
}


void
refreshScreen(void)
{
	/* Si hubo un PGUP/PGDW, un CLRSCR, o se necesitaron insertar lineas nuevas
	** se refresca la pantalla completa. */
	if( tty.ttys[tty.current].scroll_flag == TRUE )
	{
		refreshAll();
		tty.ttys[tty.current].scroll_flag = FALSE;
	}
	else if( tty.ttys[tty.current].clr_flag == TRUE )
	{
		refreshAll();
		tty.ttys[tty.current].clr_flag = FALSE; 
	}
	else
	{
		/* Si no hubo un PGUP/PGDW y base y scroll_base no coinciden, entonces
		** se debe restaurar el valor de scroll_base para volver a la posicion
		** del cursor. */
		if ( tty.ttys[tty.current].line_feed == TRUE 
				|| tty.ttys[tty.current].scroll_base != tty.ttys[tty.current].base )
		{
			tty.ttys[tty.current].scroll_base = tty.ttys[tty.current].base;
			refreshAll() ;
			tty.ttys[tty.current].line_feed = FALSE ;
		}
		else
		/* Si no es necesario un refresco completo, solo se actualizan los
		** caracteres necesarios. */
			refreshLine();
	}
	/* Se actualiza el offset de la pantalla. */
	if ( tty.ttys[tty.current].index >= tty.ttys[tty.current].base )
		screen.offset = tty.ttys[tty.current].index - tty.ttys[tty.current].base ;
	else
		screen.offset = tty.ttys[tty.current].index + VD_BUFF_SIZE - tty.ttys[tty.current].base ;
	/* Se actualiza la posicion del cursor de hardware. */
	setHwCursor();
}


void
refreshAll(void)
{
	int i ;

	/* Se actualiza la pantalla. */	
	for ( i = 0 ; i < SCREEN_SIZE ; i++)	
		screen.address[i] = 
				tty.ttys[tty.current].address[(tty.ttys[tty.current].scroll_base + i) % VD_BUFF_SIZE ];
	
}


void
refreshLine(void)
{
	int i;
	int n_chars = 0;
	
	i = screen.offset;
	
	/* Se calcula la cantidad de caracteres a actualizar. */
	if ( tty.ttys[tty.current].index >= tty.ttys[tty.current].base )
		n_chars = ( tty.ttys[tty.current].index - tty.ttys[tty.current].base) - i;
	else
		n_chars = ( tty.ttys[tty.current].index + VD_BUFF_SIZE - tty.ttys[tty.current].base ) - i;
	
	/* Se resfrescan n_chars caracteres. */	
 	if ( n_chars > 0 )
		while( n_chars > 0 )
		{
			screen.address[i++] = tty.ttys[tty.current].address[tty.ttys[tty.current].index-n_chars];
			n_chars--;
		}
	else
	{
		while( n_chars <= 0 )
		{
			screen.address[i--] = tty.ttys[tty.current].address[tty.ttys[tty.current].index-n_chars];
			n_chars++;
		}
	}
}

int
needsLineFeed(void)
{
	/* Si la diferencia entre base y index es mayor que SCREEN_SIZE, entonces
	** se necesitan nuevas lineas. */
	
	if ( (tty.ttys[tty.current].index > tty.ttys[tty.current].base && 
		(tty.ttys[tty.current].index - tty.ttys[tty.current].base > SCREEN_SIZE)) )
		return TRUE ;
	if ( (tty.ttys[tty.current].index < tty.ttys[tty.current].base &&
	     (tty.ttys[tty.current].index + VD_BUFF_SIZE - tty.ttys[tty.current].base) > SCREEN_SIZE ) )
		return TRUE ;
	return FALSE ;
}


void
insertLineFeed(void)
{
	int i ;
	int n_lines = 1;
	
	/* Se calculan la cantidad de lineas a ingresar. */
	if ( tty.ttys[tty.current].index > tty.ttys[tty.current].base )
		n_lines += (tty.ttys[tty.current].index - tty.ttys[tty.current].base - SCREEN_SIZE) / LINE_SIZE;
	else
		n_lines += ((tty.ttys[tty.current].index + VD_BUFF_SIZE - tty.ttys[tty.current].base) 
												- SCREEN_SIZE) / LINE_SIZE ;
		 
	/* Se actualiza la base. */	 
	tty.ttys[tty.current].base = (tty.ttys[tty.current].base + LINE_SIZE * n_lines ) % VD_BUFF_SIZE ;
	
	/* Se limpian n_lines en el buffer. */	
	for ( i = 0 ; i < ((LINE_SIZE * n_lines)-tty.ttys[tty.current].index % LINE_SIZE); i++)
	{
		tty.ttys[tty.current].address[(tty.ttys[tty.current].index + i++) % VD_BUFF_SIZE] = ' ' ;
		tty.ttys[tty.current].address[(tty.ttys[tty.current].index + i) % VD_BUFF_SIZE] = WHITE_TXT ;
	}
}

void
showSplashScreen(void)
{
	putc(GREEN);
	puts(WELCOME_MSG) ;
	putc(WHITE_TXT) ;
	putc(RED);
	puts("\n Welcome, type 'help' to get started. \n\n");
	putc(WHITE_TXT) ;
}


void
setHwCursor()
{
	unsigned long pos ;
	
	/* Si la base del scroll y la base del buffer no coinciden, entonces hubo
	** un scroll. */
	if ( tty.ttys[tty.current].scroll_base != tty.ttys[tty.current].base )
	  /* Se setea una posicion fuera del rango visible para esconder el cursor
	  ** en caso de haber hecho un scroll. */	
		pos = 2001 ;
	else
		pos = screen.offset/2 ;

	/* Comunicacion con el dispositivo CRTC para setear el cursor. */	

	unsigned char cursor_addressL = pos & 0x00FF ;
	unsigned char cursor_addressH = pos >> 8;
	unsigned char reg1 = 0x0E ;
	unsigned char reg2 = 0x0F ; 
	unsigned short port1 = 0x3D4 ;
	unsigned short port2 = 0x3D5 ;

	__asm__("outb %0,%1"::"a"(reg1), "Nd" (port1));
	__asm__("outb %0,%1"::"a"(cursor_addressH), "Nd" (port2));

	__asm__("outb %0,%1"::"a"(reg2), "Nd" (port1));
	__asm__("outb %0,%1"::"a"(cursor_addressL), "Nd" (port2));
}

void
insertNewline(void)
{
		int i, spaces_left ;
		
		/* Se escriben blancos en el buffer hasta que se termine la linea. */
		spaces_left = NUM_COL - (tty.ttys[tty.current].index/2 % NUM_COL);
		
		for ( i = 0 ; i < spaces_left ; i++ )
		{
			INSERTBLANK(tty.ttys[tty.current].index);
			tty.ttys[tty.current].index += 2;
		}
}

void
insertTab(void)
{
	int i ;
	
	/* Se escriben 8 blancos ene l buffer de video. */
	for ( i = 0 ; i < TAB_WIDTH ; i++ )
	{
		INSERTBLANK(tty.ttys[tty.current].index);
		tty.ttys[tty.current].index +=2;
	}
}

void
insertPageup(void)
{
	/* Se calcula al indice de la linea siguiente a la posicion de index para
	** calculos auxiliares. */
	int nextLineIndex = LINE_SIZE * ( 1 + tty.ttys[tty.current].index / LINE_SIZE );

	/* Se decrementa scroll_base en 5 lineas. */
	tty.ttys[tty.current].scroll_base -= 5 * LINE_SIZE;
	
	/* Se chequea que el scroll sea valido. */
	if( tty.ttys[tty.current].first_lap == TRUE)
	{
		if ( tty.ttys[tty.current].scroll_base < 0 )
			tty.ttys[tty.current].scroll_base = 0 ;
	}
	else
	{
		if ( tty.ttys[tty.current].scroll_base < 0 )
			tty.ttys[tty.current].scroll_base += VD_BUFF_SIZE;

		if( tty.ttys[tty.current].base < tty.ttys[tty.current].index 
				&&	tty.ttys[tty.current].scroll_base >= tty.ttys[tty.current].base
				&&	tty.ttys[tty.current].scroll_base < nextLineIndex )
			tty.ttys[tty.current].scroll_base = nextLineIndex ;
		if( tty.ttys[tty.current].base > tty.ttys[tty.current].index &&
				!(tty.ttys[tty.current].scroll_base >= nextLineIndex 
					&& tty.ttys[tty.current].scroll_base < tty.ttys[tty.current].base) )
			tty.ttys[tty.current].scroll_base = nextLineIndex ;
	}
}

void
insertPagedown(void)
{
	/* Se incrementa scroll_base en 5 lineas. */
	tty.ttys[tty.current].scroll_base = (tty.ttys[tty.current].scroll_base + 5*LINE_SIZE)% VD_BUFF_SIZE;
	
	/* Si el scroll no es valido, scroll_base se iguala a base */
	if( tty.ttys[tty.current].base < tty.ttys[tty.current].index )
	{
		if ( tty.ttys[tty.current].scroll_base >= tty.ttys[tty.current].base 
					&& tty.ttys[tty.current].scroll_base < tty.ttys[tty.current].index + 5 * LINE_SIZE)
		{
			tty.ttys[tty.current].scroll_base = tty.ttys[tty.current].base ;
		}
	}
	else 
	{	
		if ( tty.ttys[tty.current].scroll_base > tty.ttys[tty.current].base )
			tty.ttys[tty.current].scroll_base = tty.ttys[tty.current].base ;
	}
		

}

void
insertBackspace(void)
{
	/* Retrocede index dos lugares y se blanquea su posicion. */
	tty.ttys[tty.current].index -= 2;
	tty.ttys[tty.current].index += tty.ttys[tty.current].index < 0 ? VD_BUFF_SIZE : 0 ;
	INSERTBLANK(tty.ttys[tty.current].index);
}

void
insertCharacter(char c)
{
	/* Se inserta un caracter con atributo WHITE_TXT. */
	tty.ttys[tty.current].address[tty.ttys[tty.current].index++ % VD_BUFF_SIZE ] = c;
	tty.ttys[tty.current].address[tty.ttys[tty.current].index++ % VD_BUFF_SIZE ] = screen.color_att;
}

void
clearScreen(void)
{
	int i, spaces_left ;

	/* Se limpia una pantalla entera en el buffer- */
	spaces_left = LINE_SIZE - (tty.ttys[tty.current].index % LINE_SIZE); 
	for ( i = 0 ; i < SCREEN_SIZE + spaces_left; i += 2 )
	{
		tty.ttys[tty.current].address[(tty.ttys[tty.current].index+i) % VD_BUFF_SIZE ] = ' ' ;
		tty.ttys[tty.current].address[(tty.ttys[tty.current].index+i+1) % VD_BUFF_SIZE] = WHITE_TXT ; 
	}
	/* Se igualan todos los indices. */
	tty.ttys[tty.current].base = tty.ttys[tty.current].scroll_base = tty.ttys[tty.current].index ;
	screen.offset = 0 ;
}		

char *
getTty(void){
	if ( tty.current == 0)
		return "0";
	else
		return "1";

}	

