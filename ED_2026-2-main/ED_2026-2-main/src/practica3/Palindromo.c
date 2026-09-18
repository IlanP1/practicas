#include "Palindromo.h"

void verificarPalindromo(void *cadena,Pila* pila){
	void* aux;
	char* auxcadena=cadena;
	for(int i=0;auxcadena[i]!='\0';i++){
		if((auxcadena[i]>=65&&auxcadena[i]<=90)||(auxcadena[i]>=97&&auxcadena[i]<=122)){
			aux=pop(pila);
			if(*(char*)aux!=auxcadena[i]&&*(char*)aux!=auxcadena[i]+32&&*(char*)aux!=auxcadena[i]-32){
				printf("\nNo es un palindromo\n");
				return;
			}
		}
	}
	if(pilaVacia(*pila))
		printf("\nEs un palindromo\n");
	else
		printf("\nNo es un palindromo\n");
	
	
}
void verificarParentesis(void *cadena,Pila* pila){
	
	void* aux;
	char* auxcadena=cadena;
	for(int i=0;auxcadena[i]!='\0';i++){
		if(auxcadena[i]==40||auxcadena[i]==91||auxcadena[i]==123)
			push(pila,&auxcadena[i]);
		else if(auxcadena[i]==41){
			aux=pop(pila);
			if(!aux){
				printf("\nUnderflow\n");
				return;
			}
			else if(*(char*)aux!=40){
				printf("\nInvalido\n");
				return;
			}
		}
		else if(auxcadena[i]==93){
			aux=pop(pila);
			if(!aux){
				printf("\nUnderflow\n");
				return;
			}
			else if(*(char*)aux!=91){
				printf("\nInvalido\n");
				return;
			}
		}
		else if(auxcadena[i]==125){
			aux=pop(pila);
			if(!aux){
				printf("\nUnderflow\n");
				return;
			}
			else if(*(char*)aux!=123){
				printf("\nInvalido\n");
				return;
			}
		}
	}
	if(pilaVacia(*pila))
		printf("\nValido\n");
	else
		printf("\nInvalido\n");
	
}
void insertarEnPila(void *cadena,Pila* pila){
	char* auxcadena=cadena;
	for(int i=0;auxcadena[i]!='\0';i++){
		if((auxcadena[i]>=65&&auxcadena[i]<=90)||(auxcadena[i]>=97&&auxcadena[i]<=122))
			push(pila,&auxcadena[i]);
	}
}

