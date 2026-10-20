#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <arbol.h>
#include <Nodo.h>

int *crearEntero(int);
void imprimir(void*);
void insertarArbolO(Arbol *arbol,void *dato);
void eliminarDato(Arbol* arbol,void* dato);
int compararEntero(void *a,void *b);
void equilibrarArbol(Arbol* arbol);
void** llenarOrden(Arbol* arbol,void** ordenado);
void liberarNodos(Arbol* arbol);
int compararEntero(void *a,void *b);
void** llenarEquilibrado(int n,void** equilibrado,void** ordenado);

int main(void)
{
	int opc=0;
	Arbol arbol;
	arbol.raiz=NULL;
	arbol.cant=0;
	int dato=0;
	arbol.fn_comparar=compararEntero;
	do{
		system("pause");
		system("cls");
		printf("\n1. Insertar en arbol");
		printf("\n2. Eliminar dato");
		printf("\n3. Equilibrar arbol");
		printf("\n4. Mostrar arbol");
		printf("\n5. Terminar programa");
		printf("\n Ingresa una opcion: ");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				printf("Ingresa el dato que quieres insertar: ");
				scanf("%d",&dato);
				insertarArbolO(&arbol,crearEntero(dato));
			
				
			break;
			case 2:
				printf("Ingresa el dato que quieres eliminar: ");
				scanf("%d",&dato);
				eliminarDato(&arbol,&dato);
			break;
			case 3:
				equilibrarArbol(&arbol);
			
			break;
			case 4:
				imprimirArbol(arbol,imprimir);
				printf("\n");
			break;
			case 5:
				printf("\nTerminando programa");
			break;
		}
		
		
	}while(opc!=5);
	
	
	printf("\n Arbol\n");
	imprimirArbol(arbol,imprimir);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


int *crearEntero(int num)
{
	int *dato = calloc(1,sizeof(int));
	*dato = num;
	return dato;
}

void imprimir(void *dato)
{
	printf("%d",*(int*)dato);
}

void insertarArbolO(Arbol *arbol,void *dato){
		if(!arbol->raiz){
			arbol->raiz=crearNodoa(dato);
			arbol->cant++;
			return;
		}
		Nodoa *actual=arbol->raiz;
		Nodoa *padre=NULL;
		int lado=0;
		while(actual!=NULL){
			padre=actual;
			if(arbol->fn_comparar(dato,actual->dato)==-1||arbol->fn_comparar(dato,actual->dato)==0){
				actual=actual->izq;
				lado=1;
			}
			else if(arbol->fn_comparar(dato,actual->dato)==1){
				actual=actual->dch;
				lado=2;
			}
		}
		if(lado==1)
			padre->izq=crearNodoa(dato);
		else if(lado==2)
			padre->dch=crearNodoa(dato);
		arbol->cant++;
}

void eliminarDato(Arbol* arbol,void* dato){
	if(!arbol->raiz)
		return;
	Nodoa* elim=arbol->raiz;
	Nodoa* reemplazo=NULL;
	Nodoa* fondo=NULL;
	Nodoa* ep=arbol->raiz;
	int lado=0;
	int comparar=0;
	while(elim!=NULL){
		comparar=arbol->fn_comparar(dato,elim->dato);
		if(comparar==0){
			break;
		}
		else if(comparar==1){
			ep=elim;
			lado=2;
			elim=elim->dch;
		}
		else if(comparar==-1){
			ep=elim;
			lado=1;
			elim=elim->izq;
		}
	}
	if(elim==NULL){
		printf("\nEste dato no se encuantra en el arbol");
		return;
	}
	else{
		if(!elim->izq)
			reemplazo=elim->dch;
		else if(!elim->dch)
			reemplazo=elim->izq;
		else{
			reemplazo=elim->izq;
			fondo=elim->izq;
			while(fondo->dch)
				fondo=fondo->dch;
			fondo->dch=elim->dch;
		}
		if(elim==arbol->raiz){
			arbol->raiz=reemplazo;
			free(elim->dato);
			free(elim);
		}
		else{
			if(lado==1)
				ep->izq=reemplazo;
			else if(lado==2)
				ep->dch=reemplazo;
			free(elim->dato);
			free(elim);
			arbol->cant--;
		}
	}
}

void equilibrarArbol(Arbol* arbol){
	if(!arbol->raiz){
		return;
	}
	int Hi=0,Hd=0,B=0;
	Arbol arbolaux;
	arbolaux.raiz=arbol->raiz->dch;
	Hd=alturaI(arbolaux);
	arbolaux.raiz=arbol->raiz->izq;
	Hi=alturaI(arbolaux);
	B=Hd-Hi;
	if(B>=-1&&B<=1)
		return;
	else{
		int n=arbol->cant;
		void** ordenado=calloc(n,sizeof (void*));
		void** equilibrado=calloc(n,sizeof (void*));
		ordenado=llenarOrden(arbol,ordenado);
		equilibrado=llenarEquilibrado(n,equilibrado,ordenado);
		liberarNodos(arbol);
		for(int i=0;i<n;i++){
			insertarArbolO(arbol,equilibrado[i]);
		}
		free(ordenado);
		free(equilibrado);
	}
}
void** llenarOrden(Arbol* arbol,void** ordenado){
	if (!arbol->raiz)
		return NULL;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol->raiz;
	Nodoa *ultimo_visitado = NULL;
	int i=0;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = pop(&pila);			
			ordenado[i]=padre->dato;
			i++;
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = padre;
		}
	}
	return ordenado;
	
}
void liberarNodos(Arbol* arbol){
	Nodoa* elim=NULL;
	Pila pila=inicializarPila(-1);
	push(&pila,arbol->raiz);
	while(!pilaVacia(pila)){
		elim=pop(&pila);
		if(elim->izq)
			push(&pila,elim->izq);
		if(elim->dch)
			push(&pila,elim->dch);
		free(elim);
	}
	arbol->raiz=NULL;
	arbol->cant=0;
	
}
//1 4 5 6 7 8 9 10 11    7 5 4 1 6 9 10 8 11

int compararEntero(void *a,void *b){
	int aa=*(int*)a;
	int bb=*(int*)b;
	if(aa>bb)
		return 1;
	else if(aa<bb)
		return -1;
	else
		return 0;
}

void** llenarEquilibrado(int n,void** equilibrado,void** ordenado){
	Pila pilainc=inicializarPila(-1);
	Pila pilafin=inicializarPila(-1);
	int i=0;
	int inicio=0;
	int final=n-1;
	int mitad=0;
	push(&pilainc,crearEntero(inicio));
	push(&pilafin,crearEntero(final));
	while(!pilaVacia(pilainc)&&!pilaVacia(pilafin)){
		inicio=*(int*)pop(&pilainc);
		final=*(int*)pop(&pilafin);
		mitad=(inicio+final+1)/2;
		equilibrado[i]=ordenado[mitad];
		i++;
		if(mitad+1<=final){
				push(&pilainc,crearEntero(mitad+1));
				push(&pilafin,crearEntero(final));
		}
		if(mitad-1>=inicio){
			push(&pilainc,crearEntero(inicio));
			push(&pilafin,crearEntero(mitad-1));
		}
	}
	return equilibrado;
	
	
	
}

//imprimir char saltoNivel="     |"