#include <stdio.h>
#include <stdlib.h>
#include <Pila.h>
#include <iostring.h>
#include "Laberinto.h"
#include <windows.h>



Pila* resolverLab(Laberinto lab, Coordenada origen,Coordenada destino);

int main(void)
{
    Laberinto lab = crear_laberinto();
	//Movimientos mov;
	Coordenada origen = {1,1}; 
	Coordenada destino = {25,24};
	unsigned int nuevasCoor = 0;	
	inputEnteroSinSigno("\n Nuevas coordenadas? (1:SI 0:NO) : ",&nuevasCoor);
	if(nuevasCoor)
	{
		inputEntero("\n Captura Origen X: ",&origen.x);
		inputEntero(" Captura Origen Y: ",&origen.y);
		inputEntero("\n Captura Destino X: ",&destino.x);
		inputEntero(" Captura Destino Y: ",&destino.y);
	}
	setOrigen(lab,origen);
	setDestino(lab,destino);	
	
	Pila *pila = resolverLab(lab,origen,destino);
	
	
	
	
	imprimirLab(lab);
	liberarLaberinto(lab);
	eliminarPila(pila,free);
	free(pila);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


Pila* resolverLab(Laberinto lab, Coordenada origen,Coordenada destino)
{
		
	Pila *pila = crearPila();
	*pila = inicializarPila(-1);
	Coordenada *punto;
	Movimientos mov;
	Coordenada* checkpoint=NULL;

	punto = crearCoordenada(origen.x,origen.y);
	push(pila,punto);	
	

	
	while( !pilaVacia(*pila))
	{
		printf("\n Presione enter para continuar....");
		Sleep(250);
		system("cls");
		imprimirLab(lab);
		printf("\nCoordenada actual: ");
		imprimirCoordenada(punto);
		printf("\nMovimientos disponibles: \n");
		mov=movimientosPosibles(lab,*punto);
		imprimirMovimientos(mov);
		if(mov.right+mov.down+mov.left+mov.up>1){
			checkpoint=crearCoordenada(punto->x,punto->y);
			push(pila,checkpoint);
		}
		if(mov.right==1||lab[punto->x][punto->y+1]=='B'){
			
			punto->y++;
		}
		else if(mov.down==1||lab[punto->x+1][punto->y]=='B'){
			punto->x++;
	
		}
		else if(mov.left||lab[punto->x][punto->y-1]=='B'){
			punto->y--;
		}
		else if(mov.up||lab[punto->x-1][punto->y]=='B'){
			punto->x--;
		}
		else{
			
			punto=(Coordenada*)pop(pila);
			continue;
		}	
		if(lab[punto->x][punto->y]=='B'){
			printf("\nCompletaste el laberinto\n");
			return pila;
		}
		else{
			lab[punto->x][punto->y]='.';
		}
		
	}
	return pila;
}


