#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <Pila.h>
#include <Cola.h>
#include <windows.h>
#include "Palindromo.h"

void imprimir(void *);

int main(void)
{
	Pila pila = inicializarPila(-1);	
	
	int opc;
    char cadena[30];
	do{
		system("pause");
		system("cls");
		printf("\n1.Verificar parentesis");
		printf("\n2.Verificar palindromo");
		printf("\n3.Salir del programa");
		printf("\nElige una opcion: ");
		scanf("%d",&opc);
		clear_buffer();
		switch(opc){
			case 1:
				inputCadena("\n Captura cadena: ",cadena,30);
				verificarParentesis(&cadena,&pila);
				eliminarPila(&pila,NULL);
			break;
			case 2:
				inputCadena("\n Captura cadena: ",cadena,30);
				insertarEnPila(&cadena,&pila);
				verificarPalindromo(&cadena,&pila);
				eliminarPila(&pila,NULL);
			break;
			case 3:
				printf("\nTerminando programa");
			break;
			
		}
		
		
	}while(opc!=3);

    return 0;
	
	
	
}


void imprimir(void *dato)
{
	printf("%c",*(char*)dato);
}