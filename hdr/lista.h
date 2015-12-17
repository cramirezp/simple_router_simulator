#include <stdlib.h>

struct nodo_t{
	double peso;
	struct nodo_t *sig;

	void *valor;
};

struct lista_t{
	unsigned int tamano;

	struct nodo_t *puntero;
	struct nodo_t *ultimo;
};

int lista_iniciar(struct lista_t *l){
	if(l == NULL)
		return 1;

	l->tamano = 0;
	l->puntero = (struct nodo_t*) malloc(sizeof(struct nodo_t));
	l->puntero->peso  = 0.0;
	l->puntero->sig   = NULL;
	l->puntero->valor = NULL;
	l->ultimo = l->puntero->sig;

	return 0;
}

int lista_iniciada(struct lista_t *l){
	return l!=NULL && l->puntero!=NULL;
}

int lista_vaciada(struct lista_t *l){
	return !l->tamano;
}

#define lista_loop(L, i) 					\
	struct nodo_t *i;						\
	for(i=(L)->puntero;i!=NULL;i=i->sig)	\

int lista_insertar(struct lista_t *l, void *valor, double peso){
	// Insersión es ordenada
	if(l == NULL)
		return 1;
	else if(l->puntero == NULL)
		return 2;

	// Creacion de nodo
	struct nodo_t *n = (struct nodo_t*) malloc(sizeof(struct nodo_t));
	n->peso  = peso;
	n->valor = valor;
	n->sig   = NULL;

	if(l->puntero->sig == NULL){
		l->puntero->sig = n;
	}else if(n->peso >= l->ultimo->peso){
		l->ultimo->sig = n;
		l->ultimo = n;
	}else{
		struct nodo_t *i;
		for(i=l->puntero; i!=NULL; i=i->sig){
			if(n->peso > i->sig->peso)
				i->sig = n;
		}
	}

	l->tamano += 1;

	return 0;
}

void *lista_sacar(struct lista_t *l){
	if(l == NULL)
		return NULL;	// quizas algun errno
	else if(l->puntero == NULL)
		return NULL;	// quizas algun errno

	if(l->puntero->sig == NULL)
		return NULL;

	struct nodo_t *n = l->puntero->sig;
	void *v = n->valor;

	l->puntero->sig = l->puntero->sig->sig;
	free(n);

	return v;
}

void lista_imprimir(struct lista_t *l){
	lista_loop(l, i){
		printf("Peso %.2f\n", i->peso);
	}
}
