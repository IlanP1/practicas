#include "impresora.h"


void agregarArchivo(Heap* heap,char** documentos){
	
	Archivo *archivo=calloc(1,sizeof(Archivo));
	archivo->nombre=documentos[rand()%7];
	archivo->paginas=rand()%50+1;
	printf("\nNuevo archivo: \n");
	imprimirArchivo(archivo);
	insertarHeap(heap,archivo);

}

void procesarArchivo(Heap* heap){
		if(!heap->cant) return;
		void* aux;
		aux=heap->datos[0];
		heap->datos[0]=heap->datos[--heap->cant];
		heap->datos=realloc(heap->datos,heap->cant*sizeof(void*));
		printf("Se imprimio el archivo: \n");
		imprimirArchivo(aux);
		heapify_down(heap);
		free(aux);
}

void eliminarArchivo(Heap *heap){
		if(!heap->cant) return;
		imprimirArchivosHeap(heap,imprimirArchivo);
		int indice=0;
		inputEntero("\nSelecciona el archivo a eliminar: ",&indice);
		if (indice < 0 || indice >= (int)heap->cant) return;
		Archivo *elim = heap->datos[indice];
		heap->datos[indice]=heap->datos[--heap->cant];
		heap->datos=realloc(heap->datos,heap->cant*sizeof(void*));	
		heapify_up(heap);
		free(elim);
}
int compararArchivos(void *a,void *b){
	Archivo* aa, *bb;
	aa=(Archivo*)a;
	bb=(Archivo*)b;
	if(aa->paginas>bb->paginas) return 1;
	if(aa->paginas<bb->paginas) return -1;
	else return 0;
}

void imprimirArchivosHeap(Heap* heap,fn_imprimir imprimir){
	if(!heap->cant){
		printf("\nAun no hay archivos\n");
		return;
	}
	printf("\nARCHIVOS EN COLA");
	for(int i=0;i<heap->cant;i++){
		printf("\n[%d] ",i);
		imprimir(heap->datos[i]);
	}
}

void eliminarArchivos(Heap* heap){
	for(int i=0;i<heap->cant;i++){
		free(heap->datos[i]);
	}
	free(heap->datos);
	heap->datos=NULL;
	heap->cant=0;
}

void imprimirArchivos(Heap* heap,fn_imprimir imprimir){
	if(!heap->cant){
		printf("\nAun no hay archivos\n");
		return;
	}
	printf("\nARCHIVOS EN COLA");
	for(int i=0;i<heap->cant;i++){
		printf("\n[%d] ",i);
		imprimir(heap->datos[i]);
	}
	printf("\n\n");
	Arbol arbol={NULL,0};
	insertarHeapArbol(&arbol,heap);
	imprimirArbol(arbol,imprimir);
	printf("\n");
	liberarNodos(&arbol);
}

void liberarNodos(Arbol* arbol){
	if (!arbol->raiz) return;
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

void imprimirArchivo(void* dato){
	Archivo* aux=(Archivo*)dato;
	printf("%s (%d Paginas)",aux->nombre,aux->paginas);
	
}


void insertarHeapArbol(Arbol *arbol,Heap* heap){
	Cola cola=inicializarCola();
	arbol->raiz=crearNodoa(heap->datos[0]);
	arbol->cant=1;
	Nodoa* aux=arbol->raiz;
	for(int i=0;i<heap->cant/2;i++){
		if((2*i+1)<heap->cant){
			aux->izq=crearNodoa(heap->datos[2*i+1]);
			enqueue(&cola,aux->izq);
			arbol->cant++;
		}
		if((2*i+2)<heap->cant){
			aux->dch=crearNodoa(heap->datos[2*i+2]);
			enqueue(&cola,aux->dch);
			arbol->cant++;
		}
		aux=dequeue(&cola);
	}
	while(cola.cant) dequeue(&cola);
}

void imprimirArchivosLimitados(Heap* heap,fn_imprimir imprimir){
	if(!heap->cant){
		printf("\nAun no hay archivos\n");
		return;
	}
	printf("\nARCHIVOS EN COLA");
	for(int i=0;i<heap->cant&&i<5;i++){
		printf("\n[%d] ",i);
		imprimir(heap->datos[i]);
	}
}