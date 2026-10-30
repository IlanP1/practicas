#include "infixPosfix.h"

void imprimir(void *dato);

int main(){
	int opc=0;
	Arbol arbol;
	Arbol arbolaux;
	arbolaux.raiz=NULL;
	arbol.raiz=NULL;
	arbol.cant=0;
	arbolaux.cant=0;
	char cadena[LONG]={0};
	char cadenaValida[LONG]={0};
	do{
		printf("\nEXPRESION: ");
		if(arbol.raiz)
			printf("%s",cadenaValida);
		printf("\n1.Capturar expresion");
		printf("\n2.Imprimir arbol de expresion");
		printf("\n3.Evaluar expresion");
		printf("\n4.Terminar programa");
		printf("\nSelecciona una opcion: ");
		scanf("%d",&opc);
		clear_buffer();
		switch(opc){
		case 1:
			inputCadena("\nCaptura la expresion: ",cadena,LONG);
			arbolaux.raiz=NULL;
			arbolaux.raiz=crearArbol(cadena);
			if(arbolaux.raiz!=NULL){
				liberarNodos(&arbol);
				arbol.raiz=arbolaux.raiz;
				strcpy(cadenaValida,cadena);
			}
		break;
		case 2:
			if(!arbol.raiz){
				printf("\nAun no se crea un arbol");
				continue;
			}
			else{
				imprimirArbol(arbol,imprimir);
				printf("\n");
			}
		break;
		case 3:
			evaluarExpresion(&arbol,cadenaValida);
		break;
		case 4:
			printf("\nSaliendo del programa");
			liberarNodos(&arbol);
		break;
		
		}
	}while(opc!=4);


}

void imprimir(void *dato)
{
	printf("%c",*(char*)dato);
}