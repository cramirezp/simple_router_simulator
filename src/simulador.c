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

#define LAMBDA 	0.1
#define MU 		1

int main(int argc, char *argv[]){
	if(init_scheduler()){
		printf("Mala inicializacion\n");
		return 1;
	}

	scheduler_agregar_evento(ARRIBO, iacum_exp(lcgrand(0), LAMBDA));
	//scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(51), MU));

	for(int i=0;hay_evento() && i < 10000; i++){
		consumir_evento();

		switch(ultimo_evento()){
		case ARRIBO:{
			printf("%.2f\n", tiempo_simulacion());
			scheduler_agregar_evento(ARRIBO, iacum_exp(lcgrand(1), LAMBDA));
			usleep(0);
			break;
		}
		case CONSUMO:{
			printf("%.2f\n", tiempo_simulacion());
			scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(51), MU));
			sleep(0);
			break;
		}
		default:
			sleep(1);
			break;
		}
	}

	return 0;
}