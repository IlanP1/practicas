#include "alumno.h"

void registrarAlumno(Lista* lista)
{
	Alumno aux;
	size_t matri;
	printf("\ningresa la matricula del alumno a registrar:");
	scanf("%u",&matri);
	clear_buffer();
	aux.matricula=matri;
	if(buscarDato(*lista,&aux,compararMatricula)==1)
	{
		printf("\nEste alumno ya está registrado");
		return;
		
	}
	Alumno* nuevo;
	nuevo=crearAlumno(matri);
	insertarFinal(lista,nuevo);
	printf("\nAlumno agregado");
	
	
}

Alumno *crearAlumno(size_t matricula)
{
	Alumno *nuevo = calloc(1,sizeof(Alumno));
	nuevo->matricula = matricula;
	inputCadena("Captura nombre: ",nuevo->nombre,MAX);
	inputEntero("Captura semestre: ",&nuevo->semestre);
	inputFloat("Captura promedio: ",&nuevo->promedio);
	return nuevo;
}


void imprimirAlumno(void *a)
{	
	Alumno alumno = *(Alumno*)a;
	printf("%-8u | ",alumno.matricula);
	printf("%-20s | ",alumno.nombre);
	printf("%3d | ",alumno.semestre);
	printf("%.2f | ",alumno.promedio);
}

//cambiar parametros a tipo alumno
int compararMatricula(void *pa, void *pb)
{
	unsigned int a = ((Alumno*)pa)->matricula;
	unsigned int b = ((Alumno*)pb)->matricula;
	if( a>b) return 1;
	else if(a<b) return -1;
	else return 0;
}
int compararNombre(void *a, void *b)
{
	return strcmp(((Alumno*)a)->nombre,((Alumno*)b)->nombre);	
}
int compararSemestre(void *pa, void *pb)
{
	int a = ((Alumno*)pa)->semestre;
	int b = ((Alumno*)pb)->semestre;
	if( a>b) return 1;
	else if(a<b) return -1;
	else return 0;
}
int compararPromedio(void *pa, void *pb)
{
	int a = ((Alumno*)pa)->promedio;
	int b = ((Alumno*)pb)->promedio;
	if( a>b) return 1;
	else if(a<b) return -1;
	else return 0;
}

void cambiarOrden(Lista* lista){
	int opc;
	printf("\n1. Ordenar por matricula");
	printf("\n2. Ordenar por nombre");
	printf("\n3. Ordenar por semestre");
	printf("\n4. Ordenar por promedio");
	printf("\nElige como ordenar: ");
	scanf("%d",&opc);
	switch(opc){
		case 1:
			lista->comparar=compararMatricula;
		break;
		case 2:
			lista->comparar=compararNombre;
		break;
		case 3:
			lista->comparar=compararSemestre;	
		break;
		case 4:
			lista->comparar=compararPromedio;
		break;
	}
	lista->orden=ASCENDENTE;
	ordenarLista(lista,lista->comparar,lista->orden);
	
}
//encontrar la manera de que el dato que entre sea de tipo alumno
void buscarAlumno(Lista lista)
{
	Alumno aux;
	int opc;
	printf("\n1. Buscar por matricula");
	printf("\n2. Buscar por nombre");
	printf("\n3. Buscar por semestre");
	printf("\n4. Buscar por promedio");
	printf("\nElige como Buscar: ");
	scanf("%d",&opc);
	clear_buffer();
	switch(opc){
		case 1:
			printf("\nEscribe la matrícula: ");
			scanf("%u",&aux.matricula);
			clear_buffer();
			lista.comparar=compararMatricula;
		break;
		case 2:
			inputCadena("Captura nombre: ",aux.nombre,MAX);
			lista.comparar=compararNombre;
		break;
		case 3:
			inputEntero("Captura semestre: ",&aux.semestre);
			lista.comparar=compararSemestre;	
		break;
		case 4:
			inputFloat("Captura promedio: ",&aux.promedio);
			lista.comparar=compararPromedio;
		break;
	}
	if(!lista.inicio)
	{
		printf("\nNo se encuentra en la lista");
		return;
		
	}
	while(lista.inicio)
	{
		if(lista.comparar(&aux,lista.inicio->dato)==0)
		{
			imprimirAlumno(lista.inicio->dato);
			return;
		}
		lista.inicio=lista.inicio->sig;
	}
	printf("\nNo se encuentra en la lista");
	return;
	
}

void eliminarAlumno(Lista* lista)
{
	Alumno aux;
	size_t matri;
	printf("\nEscribe la matricula del alumno a eliminar: ");
	scanf("%u",&matri);
	clear_buffer();
	aux.matricula=matri;
	eliminarDato(lista,&aux,compararMatricula);
	return;
	
	
}