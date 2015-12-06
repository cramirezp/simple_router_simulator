
#include "lista.h"

struct scheduler_t{
	struct lista_evento lista;
	double tiempo_simulacion;

	enum EVENTO evento_actual;		// Tipo de evento
	double tiempo_espera_actual;	//Delta hasta siguiente evento
};

static struct scheduler_t scheduler;	// Variable global de cabecera

int init_scheduler(){
	//scheduler = (struct scheduler_t*) malloc(sizeof(struct struct scheduler_t));
	if(lista_init(&scheduler.lista) == 1)
		return 1;	// error : lista nula

	scheduler.tiempo_simulacion = 0.0;
	scheduler.evento_actual     = NINGUNO;

	return 0;
}

void scheduler_agregar_evento(enum EVENTO e, double t){
	lista_insertar(&scheduler.lista, e, t);
}

int consumir_evento(){
	if(scheduler.lista.primero == NULL)
		return 1;	// error : no se ha inicializado lista

	if(scheduler.lista.primero->sig == NULL)
		return 2;	// error : no se ha insertado ningún nodo

	scheduler.evento_actual        = scheduler.lista.primero->sig->evento;
	scheduler.tiempo_espera_actual = scheduler.lista.primero->sig->tiempo;
	scheduler.tiempo_simulacion   += scheduler.tiempo_espera_actual;

	struct nodo_evento *actual_cabeza = scheduler.lista.primero->sig;
	scheduler.lista.primero->sig           = actual_cabeza->sig;

	lista_reiniciar(&scheduler.lista);
	while(lista_siguiente(&scheduler.lista)){
		scheduler.lista.actual->tiempo -= actual_cabeza->tiempo;
	}

	free(actual_cabeza);

	return 0;
}
int hay_evento(){
	//lista_imprimir(&scheduler.lista);
	return scheduler.lista.tamano;
}

enum EVENTO ultimo_evento(){
	return scheduler.evento_actual;
}

double tiempo_simulacion(){
	return scheduler.tiempo_simulacion;
}