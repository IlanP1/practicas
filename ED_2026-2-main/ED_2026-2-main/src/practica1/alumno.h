#ifndef ALUMNO_H
#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <string.h>
#include <Lista.h>

#define ALUMNO_H
#define MAX 64


typedef struct
{
	size_t matricula;
	char nombre[MAX];
	int semestre;
	float promedio;
}Alumno;

void registrarAlumno(Lista *lista);
Alumno *crearAlumno(size_t);
void imprimirAlumno(void*);
int compararMatricula(void*,void*);
int compararNombre(void*,void*);
int compararSemestre(void*,void*);
int compararPromedio(void*,void*);
void cambiarOrden(Lista *lista);
void buscarAlumno(Lista lista);
void eliminarAlumno(Lista *lista);


#endif