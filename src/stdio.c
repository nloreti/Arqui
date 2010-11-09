/*********************************************
stdio.c

libreria estandar de entrada/salida
************************************************/

#include "../include/stdio.h"

char
getc(void)
{
	unsigned char aux = 0;
	/* Se toman scancodes siempre que no sean caracteres especiales */
	while(aux == PGUP || aux == PGDN || aux == CLRSCR || aux == RED || 
			aux == GREEN || aux == BLUE )
		aux = internalGetc();
	return (char)aux;
}

char
internalGetc(void)
{
	unsigned char aux = 0;
	while(!read(STDIN, &aux,1));
	return (char)aux;
}


void
putc(char c)
{
	write(STDOUT,&c,1);
}

void
puts(char* s)
{
	write(STDOUT,s,strlen(s));
}

int
gets(char* dest, int length)
{
	int current_index = 0;
	char c;
	int i ;
	
	/* Se levantan caracteres hasta presionar INTRO */
	while ( (c = internalGetc()) != '\n' )
	{
		switch(c)
		{
			case PGDN: case PGUP: case CLRSCR: 
				putc(c);
				break ;
			case '\b':	
				if ( current_index > 0 )
				{
					putc(c) ;
					current_index-- ;
				}
				break;
			case '\t':
				for (i = 0 ; i < TAB_WIDTH && current_index < length -1 ; i++)
				{
					dest[current_index++] = ' ' ;
					putc(' ') ;
				}
				break ;
			default:
				if( current_index < (length-1) )
				{
					dest[current_index++] = c ;
					putc(c) ;				
				}
				break ;
		}
	}
	dest[current_index] = '\0';
	putc('\n');
	return current_index;
}

int
strlen(char* str)
{
	int length = 0 ;

	while ( str[length] != '\0' )
		length++ ;

	return length ;
}

int
strcmp(char * s1, char * s2)
{
	int diff = 0 ;

	while(*s1 != '\0' && *s2 != '\0' && diff == 0)
		diff += *s1++ - *s2++ ;    

	if ( diff == 0 && *s1 - *s2 < 0 )
		return -1 ;
	if ( diff == 0 && *s1 - *s2 > 0 )
		return 1 ;

	return diff ;
}

int
isLower(char c)
{
	return c >= 'a' && c <= 'z';
}

int
isUpper(char c)
{
	return c >= 'A' && c <= 'Z';
}

int
isAlpha(char c)
{
	return isLower(c) || isUpper(c);
}


int
isDigit(char c)
{
	return c >= '0' && c <= '9';
}

int
isSpace(char c) 
{
	return ( c == '\t' || c == ' ' );
}

int
printf(char * fmt, ...)
{
	/* Se levanta la dirección del puntero al primer argumento. */
	void * arg_list = &fmt ;
	
	/* Se aumenta el puntero en 4 para obtener el puntero al siguiente
	** argumento. */
	arg_list += sizeof(void *) ;
	
	/* Se recorre la cadena fmt imprimiendo sus caracteres y, en caso de
	** encontrar el caracter '%', se procede a imprimir el siguiente argumento
	** en el formato indicado. */
	while( *fmt != '\0' )
	{
		if ( *fmt != '%' )
			putc(*fmt) ;
		else
			switch(*++fmt)
			{
				/* Caso entero. */
				case 'd': case 'i':
					printInt(*((int*)arg_list)) ;
					arg_list += sizeof(void *) ;
					break ;
				/* Caso caracter. */
				case 'c':
					putc(*((char*)arg_list)) ;
					arg_list += sizeof(void *) ;
					break ;
				/* Caso string. */
				case 's':
					puts(*((char**)arg_list)) ;
					arg_list += sizeof(void *) ;
					break ;
				/* Caso entero en formato hexa. */
				case 'x': case 'X':
					printHexa(*((int*)arg_list)) ;
					arg_list += sizeof(void *) ;
					break ; 	
				default:
					putc(*fmt) ;
					break ;
			}
		fmt++ ;
	}

}


void
printHexa(int num)
{
	int i, j ;
	unsigned char numArray[9] ;
	unsigned char b, bl, bh ;
	
	puts("0x") ;
	
	for ( i = 0, j = 0 ; i < 4 ; i++ )
	{
		b = num >> (24-i*8) ;
		bh = (b & 0xF0) >> 4 ;
		bl = b & 0x0F ;
	
		bh = bh > 9 ? bh - 10 + 'A' : bh + '0' ;
		bl = bl > 9 ? bl - 10 + 'A' : bl + '0' ;
		
		numArray[j++] = bh ;
		numArray[j++] = bl ;
	}
	numArray[j] = '\0' ;
	puts(numArray) ;
}

void
printInt(int num)
{
	int i, digit, n_digits ;
	
	if ( num < 0 )
	{
		num = -num ;
		putc('-') ;
	}
	
	n_digits = getNumDigits(num) ; 

	for ( i = 0 ; i < n_digits ; i++ )
	{
		digit = ( num / (int)pow(10, n_digits - i - 1) ) % 10 ;
		putc(digit + '0') ;
	}
}

int
pow(int base, int exp)
{
	int ans = 1;

	/* Solo puede calcular potencias con exponentes positivos */
	if (exp < 0 || ( exp == 0 && base == 0 ) )
		return 0 ;

	while ( exp-- )
		ans *= base ;

	return ans ;
}

static int
getNumDigits(int num)
{
	int n_digits = 1 ;
	
	while ( (num /= 10) > 0 )
		n_digits++ ;

	return n_digits ;
}		


int
atoi(char * str)
{
	int num = 0 ;
	int sign = 1 ;

	/* Se omiten los espacios en blanco */
	while(isSpace(*str) && *str != '\0' )
		str++ ;

	if ( *str == '\0' )
		return 0 ;

	if ( *str == '+' || *str == '-' )
		sign = *str++ == '+'? 1 : -1 ;

	while(isDigit(*str))
		num = num*10 + *str++ -'0' ;

	return num*sign ;
}

int
atox(char * str)
{
	int num = 0 ;
	char c ;

	/* Se omiten los espacios en blanco. */
	while(isSpace(*str) && *str != '\0' )
		str++ ;

	if ( *str == '\0' )
		return 0 ;

	while(isHexDigit(*str))
	{
		c = toUpper(*str++) ;
		if(isDigit(c))
			num = 16*num + c - '0';
		else
			num = 16*num + c - 'A' + 10 ;
	}
	return num ;
}

int
isHexString(char * str)
{
	/* Se omiten espacios. */
	while ( isSpace(*str) && *str != '\0' )
		*str++ ; 
	
	if ( *str == '\0' )
		return FALSE ;

	if ( *str == '+' || *str == '-' )	
  		*str++ ;
	
	while ( *str != '\0' )
		if ( !isHexDigit(*str++) )
			return FALSE ;
	return TRUE ;
}

int
isIntString(char* str)
{
	/* Se omiten espacios. */
	while ( isSpace(*str) && *str != '\0' )
		*str++ ; 
	
	if ( *str == '\0' )
		return FALSE ;

	if ( *str == '+' || *str == '-' )	
  		*str++ ;
	
	while ( *str != '\0' )
		if ( !isDigit(*str++) )
			return FALSE ;

	return TRUE ;	
}

int
isHexDigit(char c)
{
	return isDigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') ;
}
	
char
toUpper(char c)
{
	return isLower(c) ? c + 'A' - 'a' : c ;
}

