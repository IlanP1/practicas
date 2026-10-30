#ifndef InfixPosfix_H
#define InfixPosfix_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <Pila.h>
	#include <iostring.h> 
	#include <string.h>
	#include <Nodo.h>
	#include <arbol.h>
	#include <math.h>
	
	#define LONG 40
	
	int precedencia(char carac);
	char *crearChar(char caracter);
	void liberarNodos(Arbol* arbol);
	int buscarDato(char* variables,char caracter);
	void imprimirExpresion(double* valores,char* variables,void* cadena);
	void evaluarExpresion(Arbol* arbol,void* cadena);
	Nodoa* crearArbol(void* cadena);
	int verificarAritmetica(void* cadena);
	int verificarParentesis(void *cadena,Pila* pila);

#endif