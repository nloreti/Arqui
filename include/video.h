/*********************************************
video.h

manejo de video
************************************************/



#ifndef _video_
#define _video_

#include "keyboard.h"

#define WELCOME_MSG "Consola Arquitectura de Computadoras"
#define WHITE_TXT 0x07	/* Atributo de video. Letras blancas, fondo negro */

#define SCREEN_ADDRESS 0xB8000
#define WHITE_TXT 0x07	/* Atributo de video. Letras blancas, fondo negro */

#define N_TTY 4 /*Numero de tty's */

#define N_SCREENS 11/* Cantidad de pantallas que almacena el buffer de video */
#define VD_BUFF_SIZE (N_SCREENS*SCREEN_SIZE) /* Dimension del buffer de video */
#define SCREEN_SIZE (2*25*80) /* Dimension total de una pantalla */
#define NUM_COL 80	/* Cantidad de columnas de una pantalla */
#define LINE_SIZE (2*NUM_COL)	/* Dimension de una linea de una pantalla */
#define TAB_WIDTH 8	/* Dimension del caracter \n */


#define CLRSCR 4
#define RED 0x0C
#define	GREEN 0x02
#define BLUE 0x01

/* Pantalla */
typedef struct {
	char * address ;
	int offset ;
	char color_att ;
} t_screen;

/*  Buffer de video */
typedef struct {
	char* address;
	int base;
	int scroll_base;
	int index;
	char scroll_flag;
	char line_feed;
	char first_lap;
	char clr_flag;
} t_video_buffer;

/* tty */
typedef struct {
	t_video_buffer ttys[N_TTY];
	int current;
} t_tty;

/* Funcion que inicializa el buffer de video, limpiando los primeros SCREEN_SIZE
** bytes.*/
void initVideoBuffer(void);

/* Funcion que inicializa la pantalla seteando su miembro address como 
** SCREEN_ADDRESS, su miembro offset en 0 y copiando los primeriso SCREEN_SIZE 
** bytes del buffer de de video. */
void initScreen(void);

/* Funcion que muestra la imagen de inicio */
void showSplashScreen(void);

/* Funcion que refresca el contenido del buffer de video en la pantalla. */
void refreshScreen(void) ;

/* Funcion que refresca toda la pantalla con el contenido del buffer. */
void refreshAll(void) ;

/* Funcion que refresca los caracteres modificados en el buffer a pantalla */
void refreshLine(void) ;

/* Funcion que escribe que copia una cantidad count de caracteres tomados de la
** string str. */
void writeToVideoBuffer(char * str, int count) ;

/* Funcion que */
void insertLineFeed(void) ;

/* Funcion que fija el cursor de hardware segun el miembro offset de la 
** pantalla. */
void setHwCursor(void) ;

/* Funcion que devuelve TRUE si se deben insertar nuevas lineas y FALSE sino. */
int needsLineFeed(void) ;

/* Funcion que hace retroceder 1 caracter al buffer de video e inserta un
** blanco. */
void insertBackspace(void);

/* Funcion que inserta blancos en el buffer hasta que finalice la linea */
void insertNewline(void);

/* Funcion que inserta 8 blancos en el buffer de video */
void insertTab(void);

/* Funcion que altera el miembro scroll_base del buffer de video para que se
** scrollee la pantalla */
void insertPagedown(void);

/* Funcion que altera el miembro scroll_base del buffer de video para que se
** scrollee la pantalla hacia arriba */
void insertPageup(void);

/* Funcion que inserta el caracter c en el buffer de video. */
void insertCharacter(char c);

/* Funcion que limpia SCREEN_SIZE bytes del buffer de video y acomoda los
** indices limpiar la pantalla.  
*/
void clearScreen(void);

/* 
*/
char *
getTty(void);

void
changeTty(char number);
#endif
