#include "Cancion.h"


Canciones cargarCanciones(void)
{
	static Cancion biblioteca[] = 
	{
		(Cancion){"Despacito","Luis Fonsi",2017},
		(Cancion){"Gangnam Style","PSY",2012},
		(Cancion){"Fein","Travis Scott",2023},
		(Cancion){"ROS","Mac Miller",2015},
		(Cancion){"Recorde","Milo j",2025},
		(Cancion){"Around me","Metro Boomin",2022},
		(Cancion){"Cinderella","Mac Miller",2016},
		(Cancion){"I Think","Tyler, The Creator",2019},
		(Cancion){"Concrete","Malcolm Todd",2025},
		(Cancion){"Jet Fuel","Mac Miller",2018},
		(Cancion){"Always","Daniel Caesar",2023},
		(Cancion){"Confident","Justin Bieber",2013},
		(Cancion){"Milagrosa","Milo j",2024},
		(Cancion){"Dont Leave","Giveon",2025},
		(Cancion){"MUTT","Leon Thomas",2024}	
	};	
	static Canciones canciones;
	canciones.cancion = biblioteca;
	canciones.cant = sizeof(biblioteca)/sizeof(Cancion);
	return canciones;
}

void imprimirCanciones(Canciones canciones)
{
	printf("\n Canciones TOTAL:%d",canciones.cant);
	for(int i = 0 ; i< canciones.cant; i++)
	{
		printf("\n[%d]",i);
		imprimirCancion(&canciones.cancion[i]);
	}
}

void imprimirCancionActual(Nodod *cancionActual)
{
	
	printf("\n");
	if(!cancionActual){
		printf("Ninguna <<-- Ninguna -->> Ninguna");
		return;
	}
	if(!cancionActual->ant){
		printf(" Ninguna ");
	}
	else{
		printf(" %s ",((Cancion*)(cancionActual->ant->dato))->nombre);
	}
	printf("<<--");
	printf(" %s ",((Cancion*)(cancionActual->dato))->nombre);
	printf("-->>");
	if(!cancionActual->sig){
		printf(" Ninguna ");
	}
	else{
		printf(" %s ",((Cancion*)(cancionActual->sig->dato))->nombre);
	}
	
}

void imprimirCancion(void *dato)
{
	Cancion *cancion = dato;
	printf(" %-20s ",cancion->nombre);
	printf("| %-20s ",cancion->autor);
	printf("| %hu ",cancion->release_date);
}
void imprimirNombre(void *dato)
{
	Cancion *cancion = dato;
	printf(" %-20s ",cancion->nombre);	
} 

void eliminarCancion(ListaD *lista,fn_imprimir imprimir,Nodod **cancionActual)
{
	int opc;
	Nodod *aux;
	aux=lista->inicio;
	imprimirListaRep(*lista,imprimir);
	printf("\nElige la cancion que quieres eliminar: ");
	scanf("%d",&opc);
	clear_buffer();
	if(opc<0&&opc>=lista->cant){
		printf("\nOpcion invlaida");
		return;
	}
	if(opc==0){
		aux=lista->inicio;
		lista->inicio=lista->inicio->sig;
		if(aux==*cancionActual)
			*cancionActual=lista->inicio;
		free(aux);
		aux=NULL;
		lista->cant--;
		return;
	}
	else if(opc==(lista->cant)-1){
		aux=lista->fin;
		lista->fin=lista->fin->ant;
		if(aux==*cancionActual)
			*cancionActual=lista->inicio;
		free(aux);
		aux=NULL;
		lista->cant--;
		return;
	}
	else if(opc>0||opc<(lista->cant)-1){
		aux=lista->inicio->sig;
		for(int i=1;i<(lista->cant)-1;i++){
			if(i==opc){
				aux->ant->sig=aux->sig;
				aux->sig->ant=aux->ant;
				if(aux==*cancionActual)
					*cancionActual=lista->inicio;
				free(aux);
				aux=NULL;
				lista->cant--;
				return;
			}
			aux=aux->sig;
		}
	}
	
}


void agregarCancion(ListaD *lista,Canciones canciones,fn_imprimir imprimir)
{
	int opc;
	Cancion *cancionaux;
	Nodod *aux,*nuevo;
	imprimirCanciones(canciones);
	printf("\nElige la cancion que quieres agregar: ");
	scanf("%d",&opc);
	clear_buffer();
	if(opc>=canciones.cant&&opc<0){
		printf("\nOpción invalida");
		return;
	}
	printf("\n");
	imprimirCancion(&canciones.cancion[opc]);
	cancionaux=&canciones.cancion[opc];
	if(!lista->inicio){
		insertarFinalD(lista,cancionaux);
		return;
	}
	imprimirListaRep(*lista,imprimir);
	printf("\nEn que posicion quieres colocar la cancion: ");
	scanf("%d",&opc);
	clear_buffer();
	if(opc<0&&opc>lista->cant)
	{
		printf("\nOpcion invalida");
		return;
	}
	else if(opc==0){
		insertarInicioD(lista,cancionaux);
		return;
	}	
	else if(opc>0&&opc<lista->cant)
	{
		nuevo=crearNodod(cancionaux);
		aux=lista->inicio->sig;
		for(int i=1;i<lista->cant;i++){
			if(i==opc){
				nuevo->sig=aux;
				nuevo->ant=aux->ant;
				aux->ant=nuevo;
				nuevo->ant->sig=nuevo;
				lista->cant++;
				return;
			}
			aux=aux->sig;
		}
	}
	else if(opc==lista->cant){
		insertarFinalD(lista,cancionaux);
		return;
	}	
}

void bucleActivado(ListaD *lista)
{
	if (!lista->inicio || !lista->fin) 
		return;
	lista->fin->sig=lista->inicio;
	lista->inicio->ant=lista->fin;
	
}

void bucleDesactivado(ListaD *lista)
{
	if (!lista->inicio || !lista->fin) 
		return;
	lista->fin->sig=NULL;
	lista->inicio->ant=NULL;
}
void imprimirListaRep(ListaD lista,fn_imprimir imprimir)
{
	
	if(!lista.inicio){
		printf("\nNo hay canciones en la lista de reproduccion");
		return;
	}
	Nodod *aux = lista.inicio;
	int i=0;
	do
	{
		printf("\n[%d] ",i);
		imprimir(aux->dato);
		aux = aux->sig;
		i++;
	}while( aux && aux!= lista.inicio);
}