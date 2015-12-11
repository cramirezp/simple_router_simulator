#include <stdlib.h>

enum EVENTO {ARRIBO, CONSUMO, M_NPAQUETES, M_TESPERA, NINGUNO};

struct nodo_evento{
	enum EVENTO evento;
	double tiempo;

	struct nodo_evento *sig;
};

struct lista_evento{
	int tamano;
	struct nodo_evento *primero;
	struct nodo_evento *actual;
};

int lista_init(struct lista_evento *lista){
	if(lista == NULL)
		return 1;

	lista->tamano = 0;
	lista->primero = (struct nodo_evento*) malloc(sizeof(struct nodo_evento));
	lista->primero->sig = NULL;
	lista->actual = lista->primero;

	return 0;
}

int lista_vacia(struct lista_evento *lista){
	return lista->tamano;
}

int lista_siguiente(struct lista_evento *lista){
	if(lista == NULL)
		return 0;

	if(lista->actual == NULL)
		return 0;

	lista->actual = lista->actual->sig;

	if(lista->actual == NULL)
		return 0;

	return 1;
}

void lista_reiniciar(struct lista_evento *lista){
	if(lista != NULL)
		lista->actual = lista->primero;
}

void lista_insertar(struct lista_evento *lista, enum EVENTO e, double t){
	// 

	if(lista == NULL)
		return;

	struct nodo_evento *nodo = (struct nodo_evento*) malloc(sizeof(struct nodo_evento));
	nodo->evento = e;
	nodo->tiempo = t;
	nodo->sig = NULL;

	if(lista->primero->sig == NULL){
		lista->primero->sig = nodo;
		lista->actual  = lista->primero;
	}else{
		// No deberia haber problemas con lista->actual==NULL
		lista_reiniciar(lista);
		do{
			if(lista->actual->sig != NULL){
				if (lista->actual->sig->tiempo > t){
					nodo->sig = lista->actual->sig;
					lista->actual->sig = nodo;
					break;
				}
			}else{
				lista->actual->sig = nodo;
				nodo->sig = NULL;
				break;
			}
		}while(lista_siguiente(lista));
	}

	lista->tamano += 1;
}

void lista_imprimir(struct lista_evento *lista){
	lista_reiniciar(lista);
	while(lista_siguiente(lista)){
		printf("Evento %d -> t = %.1f \n", lista->actual->evento, lista->actual->tiempo);
	}
}
