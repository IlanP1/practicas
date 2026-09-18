#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <ListaD.h>
#include <windows.h>
#include "Cancion.h"


int main(void)
{
	Nodod *cancionActual=NULL;
    int option,corre_programa;
	fn_cambiarBucle cambiarBucle;
	fn_imprimir imprimir;
	cambiarBucle=bucleActivado;
	Canciones canciones = cargarCanciones();
	corre_programa=1;
	ListaD lista=inicializarListaD();
	cancionActual=lista.inicio;
    while(corre_programa)
    {
		system("cls");
        printf("\n\r");
        printf("\n\r");
		imprimirCancionActual(cancionActual);
        printf("\n\r [0] BUCLE");
        printf("\n\r [1] ANTERIOR");
        printf("\n\r [2] SIGUIENTE");
        printf("\n\r [3] AGREGAR CANCION");
        printf("\n\r [4] MOSTRAR LISTA DE REPRODUCCION");
        printf("\n\r [5] QUITAR CANCION");
        printf("\n\r [6] REINICIAR REPRODUCCION");
        printf("\n\r [7] TERMINAR PROGRAMA");

        printf("\n\r Escoge opcion: ");
        scanf("%d",&option);
		clear_buffer();
		switch(option)
        {
        case 0:
                if(cambiarBucle==bucleActivado){
					cambiarBucle=bucleDesactivado;
				}
				else if(cambiarBucle==bucleDesactivado){
					cambiarBucle=bucleActivado;
				}
				cambiarBucle(&lista);
                break;
        case 1:
				if(cancionActual&&cancionActual->ant)
					cancionActual=cancionActual->ant;
                //ACTUALIZA EL APUNTADOR DE LA ELEMENTO ACTUAL EN REPRODUCCION AL ANTERIOR
                break;
        case 2:
				if(cancionActual&&cancionActual->sig)
					cancionActual=cancionActual->sig;
                //ACTUALIZA EL APUNTADOR DE LA ELEMENTO ACTUAL EN REPRODUCCION AL SIGUIENTE
                break;
        case 3:
				imprimir=imprimirCancion;
				agregarCancion(&lista,canciones,imprimir);
				if(!cancionActual)
					cancionActual=lista.inicio;
				cambiarBucle(&lista);
                //SE MUESTRA UN MENU CON LAS CANCIONES DISPONIBLES
                //SE SELECCIONA LA CANCION
                //SE MUESTRA LA COLA DE REPRODUCCION
                //SE SELECCIONA EN QUE POSICION DE LA COLA SE AGREGARA
                break;
        case 4:
				imprimir=imprimirNombre;
				imprimirListaRep(lista,imprimir);
                //SE MUESTRA LA COLA DE REPRODUCCION 
                break;
        case 5:
				imprimir=imprimirNombre;
				eliminarCancion(&lista,imprimir,&cancionActual);
				cambiarBucle(&lista);
                //SE MUESTRA UN MENU CON LAS CANCIONES DE LA COLA DE REPRODUCCION
                //SE SELECCIONA UNA OPCION Y SE ELIMINA
                break;
        case 6:
				cancionActual=lista.inicio;
                //LA POSICION ACTUAL CAMBIA AL INICIO DE LA COLA DE REPRODUCCION
                break;
        case 7:
                corre_programa=0;
                break;
        default:
                break;
        }
		clear_buffer();
    }
    printf("\n FIN DE PROGRAMA \n\r");
    return 0;
}