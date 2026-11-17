#ifndef IMPRESORA_H
#define IMPRESORA_H

#include<heap.h>
#include<iostring.h>
#include<time.h>
#include<Cola.h>

typedef struct
{
	int paginas;
	char* nombre;

}Archivo;

int compararArchivos(void *a,void *b);
void agregarArchivo(Heap* heap,char** documentos);
void procesarArchivo(Heap* heap);
void eliminarArchivo(Heap *heap);
void imprimirArchivosHeap(Heap* heap,fn_imprimir imprimir);
void eliminarArchivos(Heap* heap);
void imprimirArchivos(Heap* heap,fn_imprimir imprimir);
void liberarNodos(Arbol* arbol);
void imprimirArchivo(void* dato);
void insertarHeapArbol(Arbol *arbol,Heap* heap);
void imprimirArchivosLimitados(Heap* heap,fn_imprimir imprimir);

#endif
