#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <Lista.h>
#include <windows.h>
#include "alumno.h"



int main(void)
{
	int opc;
	Lista lista=inicializarLista();
	lista.comparar=compararMatricula;
	do
	{
		system("cls");
		printf("\n1. Regsitrar alumno");
		printf("\n2. Desplegar alumnos");
		printf("\n3. Reordenar");
		printf("\n4. Buscar alumno");
		printf("\n5. Borrar alumno");
		printf("\n6. Finalizar programa");
		printf("\nElige una opcion: ");
		scanf("%d",&opc);
		switch(opc)
		{
			case 1:
				registrarAlumno(&lista);
			break;
			case 2:
				imprimirLista(lista,imprimirAlumno);
			break;
			case 3:
				cambiarOrden(&lista);
			break;
			case 4:
				buscarAlumno(lista);
			break;
			case 5:
				eliminarAlumno(&lista);
			break;
			case 6:
				printf("\nFinalizando programa\n");
			break;
			
		}
		lista.orden=ASCENDENTE;
		ordenarLista(&lista,lista.comparar,lista.orden);
		system("pause");
	}while(opc!=6);
	return 0;
	
}