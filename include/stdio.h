/*********************************************
stdio.h

************************************************/

#ifndef _stdio_
#define _stdio_

#include "klibc.h"
#include "defs.h"

/* Funcion que retorna la representacion hexadecimal del string 'str'. */	
int atox(char * str);

/* Funcion que retorna la representacion decimal del string 'str'. */	
int atoi(char * str);

/* Funcion que retorna cualquier scancode que llegue del teclado, siempre que
** este no corresponda al scancode de 'Page Up' o 'Page Down' */
char getc(void);

/* Funcion que retorna cualquier scancode que llegue del teclado. */	
char internalGetc(void);

/* Funcion que imprimie el caracter 'c' en salida estandar. */	
void putc(char c);

/* Funcion que imprime el string 's' en salida estandar. */	
void puts(char* s);

/* Funcion que imprime en buffer de video un string recibido por teclado. */
int gets(char* dest, int length);

/* Funcion que retorna el largo del string 'str'. */
int strlen(char* str);

/* Funcion que retorna un numero negativo si s1 < s2, positivo si s1 > s2, 
** 0 si son iguales. */	
int strcmp(char * s1, char * s2);

/* Funcion que retorna 1 si el argumento es un caracter en minuscula, 0 sino. */	
int isLower(char c);

/* Funcion que retorna 1 si el argumento es un caracter en mayuscula, 0 sino. */	
int isUpper(char c);

/* Retorna 1 si el c representa una letra, ya sea mayuscula o minuscula, 0 sino */
int isAlpha(char c);

/* Retorna 1 si el argumento representa un numero en sistema hexadecimal, 0 sino. */
int isHexString(char * str);

/* Retorna 1 si el argumento representa un entero, 0 sino. */	
int isIntString(char* str);

/* Funcion que retorna la representacion a mayuscula de 'c', si tiene. 
** Retorna 'c' sino. */	
char toUpper(char c);

/* Funcion que retoran 1 si el argumento es un numero en sistema hexadecimal,
** 0 sino. */	
int isHexDigit(char c);

/* Funcion que retorna 1 si el argumento es un digito, 0 sino. */	
int isDigit(char c);

/* Funcion que retorna 1 si el argumento es un espacio, 0 sino. */
int isSpace(char c);

/* Funcion para imprimir en salida estandar con formato (int, string, char, hexa). */	
int printf(char * fmt, ...);

/* Funcion para imprimir un numero en sistema hexadecimal en salida estandar. */	
void printHexa(int num);

/* Funcion para imprimir un entero en salida estandar. */
void printInt(int num);

/* Funcion para calcular potencia. */
static int pow(int base, int exp);

/* Funcion que retorna la cantidad de digitos de un entero. */	
static int getNumDigits(int num);

#endif
