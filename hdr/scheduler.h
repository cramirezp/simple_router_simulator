#include "lista.h"

enum EVENTO {ARRIBO, CONSUMO, M_NPAQUETES, M_TESPERA, NINGUNO};

struct evento_t{
	enum EVENTO tipo;
	double tiempo;
};

struct scheduler_t{
	struct lista_t lista_eventos;
	double tiempo_simulacion;

	enum EVENTO evento_actual;
};

static struct scheduler_t scheduler;	// Variable global de cabecera

int scheduler_inicializar(){
	//scheduler = (struct scheduler_t*) malloc(sizeof(struct struct scheduler_t));
	if(lista_iniciar(&scheduler.lista_eventos))
		return 1;	// error : lista nula

	scheduler.tiempo_simulacion = 0.0;
	scheduler.evento_actual     = NINGUNO;

	return 0;
}

int scheduler_agregar_evento(enum EVENTO e, double delta_t){
	if(lista_iniciada(&scheduler.lista_eventos))
		return 1;	// error : no se ha inicializado lista

	// Creacion de evento
	struct evento_t *nuevo_evento = (struct evento_t*) malloc(sizeof(struct evento_t));
	nuevo_evento->tipo   = e;
	nuevo_evento->tiempo = scheduler.tiempo_simulacion + delta_t;

	// Agregar evento a lista
	lista_insertar(&scheduler.lista_eventos, (void*) nuevo_evento, nuevo_evento->tiempo);

	return 0;
}

int scheduler_consumir_evento(){
	/* Actualiza tiempo de simulacion y registra evento más rapido de los sque tenga en lista */

	if(lista_iniciada(&scheduler.lista_eventos))
		return 1;	// error : no se ha inicializado lista

	if(lista_vaciada(&scheduler.lista_eventos))
		return 2;	// error : no se ha insertado ningún nodo

	struct evento_t *e = (struct evento_t*) lista_sacar(&scheduler.lista_eventos); 

	scheduler.evento_actual     = e->tipo;
	scheduler.tiempo_simulacion = e->tiempo;

	free(e);

	return 0;
}

int hay_evento(){
	return scheduler.lista_eventos.tamano;
}

enum EVENTO evento_actual(){
	return scheduler.evento_actual;
}

double tiempo_simulacion(){
	return scheduler.tiempo_simulacion;
}

void scheduler_imprimir(){
	lista_imprimir(&scheduler.lista_eventos);
}