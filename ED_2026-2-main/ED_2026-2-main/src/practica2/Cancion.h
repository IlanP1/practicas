#ifndef CANCION_H
#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <string.h>
#include <ListaD.h>
#include <nodo.h>

#define MAXCADENA 20

typedef void (*fn_cambiarBucle)(ListaD*);

typedef struct 
{
    char nombre[MAXCADENA];
    char autor[MAXCADENA];
    short int release_date;
}Cancion;

typedef struct
{
	Cancion *cancion;
	size_t cant;
}Canciones;


Canciones cargarCanciones(void); 
void imprimirCanciones(Canciones);
void imprimirCancionActual(Nodod *cancionActual);
void imprimirCancion(void*);
void imprimirNombre(void*);
void eliminarCancion(ListaD *lista,fn_imprimir imprimir,Nodod **cancionActual);
void agregarCancion(ListaD *lista,Canciones canciones,fn_imprimir imprimir);
void bucleActivado(ListaD *lista);
void bucleDesactivado(ListaD *lista);
void imprimirListaRep(ListaD lista,fn_imprimir imprimir);

#endif