#include "infixPosfix.h"


int verificarParentesis(void *cadena,Pila* pila){
	
	void* aux;
	char* auxcadena=cadena;
	for(int i=0;auxcadena[i]!='\0';i++){
		if(auxcadena[i]==40||auxcadena[i]==91||auxcadena[i]==123)
			push(pila,&auxcadena[i]);
		else if(auxcadena[i]==41){
			aux=pop(pila);
			if(!aux||*(char*)aux!=40){
				while(!pilaVacia(*pila))
					pop(pila);
				return 0;
			}
		}
		else if(auxcadena[i]==93){
			aux=pop(pila);
			if(!aux||*(char*)aux!=91){
				while(!pilaVacia(*pila))
					pop(pila);
				return 0;
			}
		}
		else if(auxcadena[i]==125){
			aux=pop(pila);
			if(!aux||*(char*)aux!=123){
				while(!pilaVacia(*pila))
					pop(pila);
				return 0;
			}
		}
	}
	if(pilaVacia(*pila))
		return 1;
	else{
		while(!pilaVacia(*pila))
			pop(pila);
		return 0;
	}
	
}


int verificarAritmetica(void* cadena){
	
	char* aux=cadena;
	int i=0;
	while(aux[i]!='\0'){
		while(aux[i]==40) i++;
		if((aux[i]<'a'||aux[i]>'z')&&(aux[i]<'A'||aux[i]>'Z')){
			return 0;
		}
		else{
			i++;
			while(aux[i]==41)i++;
			if(aux[i]=='\0') return 1;
			if(aux[i]==42||aux[i]==43||aux[i]==45||aux[i]==47||aux[i]==94){
				i++;
				continue;
			}
			else
				return 0;
		}
	}
	return 0;
}


Nodoa* crearArbol(void* cadena){
	Pila pila =inicializarPila(-1);
	char *auxCadena=cadena;
	if(!verificarParentesis(cadena,&pila)){
		printf("\nCadena invalida");
		return NULL;
	}
	if(!verificarAritmetica(cadena)){
		printf("\nCadena invalida");
		return NULL;
	}
	char posfix[LONG]={0};
	int contP=0;
	
	for(int cont=0;auxCadena[cont]!='\0';cont++){
		if((auxCadena[cont]>='a'&&auxCadena[cont]<='z')||(auxCadena[cont]>='A'&&auxCadena[cont]<='Z')){
			posfix[contP++]=auxCadena[cont];
			
		}
		else if(auxCadena[cont]==42||auxCadena[cont]==43||auxCadena[cont]==45||auxCadena[cont]==47||auxCadena[cont]==94){
			if(pilaVacia(pila)||*(char*)peek(pila)==40||precedencia(auxCadena[cont])>precedencia(*(char*)peek(pila))){
				push(&pila,auxCadena+cont);
			}
			else{
				while(!pilaVacia(pila)&&precedencia(*(char*)peek(pila))>=precedencia(auxCadena[cont])&&*(char*)peek(pila)!=40){
					posfix[contP++]=*(char*)pop(&pila);
				}
				push(&pila,auxCadena+cont);
			}
		}
		else if(auxCadena[cont]==40){
			push(&pila,auxCadena+cont);
		}
		else if(auxCadena[cont]==41){
			while(*(char*)peek(pila)!=40){
				posfix[contP++]=*(char*)pop(&pila);
			}
			pop(&pila);
		}	
	}
	while(!pilaVacia(pila)){
		posfix[contP++]=*(char*)pop(&pila);
	}
	posfix[contP]='\0';
	Nodoa* aux=NULL;
	for(int cont=0;posfix[cont]!='\0';cont++){
		if((posfix[cont]>='a'&&posfix[cont]<='z')||(posfix[cont]>='A'&&posfix[cont]<='Z')){
			push(&pila,crearNodoa(crearChar(posfix[cont])));
		}
		else if(posfix[cont]==42||posfix[cont]==43||posfix[cont]==45||posfix[cont]==47||posfix[cont]==94){
			aux=crearNodoa(crearChar(posfix[cont]));
			aux->dch=(Nodoa*)pop(&pila);
			aux->izq=(Nodoa*)pop(&pila);
			push(&pila,aux);
		}
	}
	printf("\nExpresion capturada");
	return (Nodoa*)pop(&pila);
}

void evaluarExpresion(Arbol* arbol,void* cadena){
	char variables[LONG]={0};
	double valores[LONG]={0};
	int pos=0;
	if (!arbol->raiz){
		printf("\nAun no capturas la expresion");
		return ;
	}
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol->raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = pop(&pila);			
			if((*(char*)(padre->dato)>='a'&&*(char*)(padre->dato)<='z')||(*(char*)(padre->dato)>='A'&&*(char*)(padre->dato)<='Z')){
				if(buscarDato(variables,*(char*)(padre->dato))==-1){
					printf("\n Ingresa el valor de la variable %c:",*(char*)(padre->dato));
					inputDouble("",&valores[pos]);
					variables[pos++]=*(char*)(padre->dato);
				}
			}
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = padre;
		}
	}
	
	actual = arbol->raiz;
	ultimo_visitado = NULL;
	double izq=0;
	double dch=0;
	double resultados[LONG]={0};
	int cima=0;
	
	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
			{
				if((*(char*)(padre->dato)<'a'||*(char*)(padre->dato)>'z')&&(*(char*)(padre->dato)<'A'||*(char*)(padre->dato)>'Z')){
					if((*(char*)(padre->dch->dato)<'a'||*(char*)(padre->dch->dato)>'z')&&(*(char*)(padre->dch->dato)<'A'||*(char*)(padre->dch->dato)>'Z')){
						dch=resultados[--cima];
					}
					else{
						dch=valores[buscarDato(variables,*(char*)(padre->dch->dato))];
					}
					if((*(char*)(padre->izq->dato)<'a'||*(char*)(padre->izq->dato)>'z')&&(*(char*)(padre->izq->dato)<'A'||*(char*)(padre->izq->dato)>'Z')){
						izq=resultados[--cima];
					}
					else{
						izq=valores[buscarDato(variables,*(char*)(padre->izq->dato))];
					}
					switch(*(char*)(padre->dato)){
						case '+':
							resultados[cima++]=izq+dch;
						break;
						case '-':
							resultados[cima++]=izq-dch;
						break;
						case '*':
							resultados[cima++]=izq*dch;
						break;
						case '/':
							resultados[cima++]=izq/dch;
						break;
						case '^':
							resultados[cima++]=pow(izq,dch);
						break;
					}
				}
				ultimo_visitado = pop(&pila);
			}
		}
	}
	imprimirExpresion(valores,variables,cadena);
	printf("= %g",resultados[--cima]);
	return;
}

void imprimirExpresion(double* valores,char* variables,void* cadena){
	char* auxCadena=cadena;
	printf("\n");
	for(int i=0;auxCadena[i]!='\0';i++){
		if((auxCadena[i]<'a'||auxCadena[i]>'z')&&(auxCadena[i]<'A'||auxCadena[i]>'Z'))
			printf("%c",auxCadena[i]);
		else{
			printf("%g",valores[buscarDato(variables,auxCadena[i])]);
		}
	}
}

int buscarDato(char* variables,char caracter){
	for(int i=0;variables[i]!='\0';i++){
		if(variables[i]==caracter)
			return i;
	}
	return -1;
}

//cada que padre sea un signo ya debería tener derecha e izquierda guardado

void liberarNodos(Arbol* arbol){
	if(!arbol->raiz)
		return;
	Nodoa* elim=NULL;
	Pila pila=inicializarPila(-1);
	push(&pila,arbol->raiz);
	while(!pilaVacia(pila)){
		elim=pop(&pila);
		if(elim->izq)
			push(&pila,elim->izq);
		if(elim->dch)
			push(&pila,elim->dch);
		free(elim->dato);
		free(elim);
	}
	arbol->raiz=NULL;
	arbol->cant=0;
	
}

char* crearChar(char caracter)
{
	char *dato = calloc(1,sizeof(char));
	*dato = caracter;
	return dato;
}

int precedencia(char carac){
	switch(carac){
		case '+':
			return 1;
		break;
		case '-':
			return 1;
		break;
		case '*':
			return 2;
		break;
		case '/':
			return 2;
		break;
		case '^':
			return 3;
		break;
	}
	return 0;
}