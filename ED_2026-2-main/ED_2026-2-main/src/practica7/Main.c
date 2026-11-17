#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <Nodo.h>
#include <heap.h>
#include <impresora.h>

int *crearEntero(int);
int compararEntero(void*,void*);
void imprimir(void*);


int main(void)
{
	char* documentos[7]={"ensayo","proyecto","libro","reporte","tarea","guia","practica"};
	srand(time(NULL));
	Heap heap = {NULL,0,HEAPMIN,compararArchivos};
	int opc=0;
	do{
		printf("\n");
		system("pause");
		system("cls");
		imprimirArchivosLimitados(&heap,imprimirArchivo);
		printf("\n");
		printf("\n----MENU----");
		printf("\n1.Cambiar prioridad");
		printf("\n2.Mostrar cola de impresion");
		printf("\n3.Agregar archivo");
		printf("\n4.Imprimir");
		printf("\n5.Eliminar archivo");
		printf("\n6.Eliminar todos los archivos");
		printf("\n7.Terminar Programa");
		inputEntero("\nElige una opcion: ",&opc);
		switch(opc){
			case 1:
				heap.type=heap.type*-1;
				heapify_up(&heap);
			break;
			case 2:
				imprimirArchivos(&heap,imprimirArchivo);
			break;
			case 3:
				agregarArchivo(&heap,documentos);
			break;
			case 4:
				procesarArchivo(&heap);
			break;
			case 5:
				eliminarArchivo(&heap);
			break;
			case 6:
				eliminarArchivos(&heap);
			break;
			case 7:
				printf("Terminando programa");
				eliminarArchivos(&heap);
			break;
			
		}
	}while(opc!=7);
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

int compararEntero(void *pa,void *pb)
{
	int a = *(int*)pa;
	int b = *(int*)pb;
	if(a<b)return -1;
	if(a>b)return 1;
	else return 0;
}


