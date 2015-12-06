/*************************************************************************
* Simulador servicio de router con una fila de espera.
* Arribo y consumo son V.A. exponenciales de parametros lambda y mu.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lcgrand.h"
#include "scheduler.h"
#include "exponencial.h"
#include "fila.h"

#define LAMBDA 	0.1
#define MU 		1

int main(int argc, char *argv[]){
	if(init_scheduler()){
		printf("Error inicializacion scheduler\n");
		return 1;
	}

	struct fila_t fila;
	if(init_fila(&fila)){
		printf("Error inicializacion fila\n");
		return 2;
	}

	scheduler_agregar_evento(ARRIBO, iacum_exp(lcgrand(0), LAMBDA));
	scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(51), MU));

	for(int i=0; hay_evento() && i < 10000; i++){
		consumir_evento();

		switch(ultimo_evento()){
		case ARRIBO:{
			fila_recibir_paquete(&fila);
			fila_imprimir(&fila);

			//printf("%.2f\n", tiempo_simulacion());
			scheduler_agregar_evento(ARRIBO, iacum_exp(lcgrand(1), LAMBDA));
			break;
		}
		case CONSUMO:{
			fila_consumir_paquete(&fila);
			fila_imprimir(&fila);

			//printf("%.2f\n", tiempo_simulacion());
			scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(51), MU));
			break;
		}
		default:
			break;
		}

		usleep(0);
	}

	return 0;
}