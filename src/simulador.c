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

#define N_EVENTOS 1000000L			// -1 maxima espera

#define LAMBDA 	1
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
	scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(49), MU));

	for(unsigned long i=0; hay_evento() && i < N_EVENTOS; i++){
		consumir_evento();

		switch(ultimo_evento()){
		case ARRIBO:{
			fila_recibir_paquete(&fila);

			scheduler_agregar_evento(ARRIBO, iacum_exp(lcgrand(1), LAMBDA));
			scheduler_agregar_evento(M_NPAQUETES, 0);
			break;
		}
		case CONSUMO:{
			fila_consumir_paquete(&fila);

			scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(51), MU));
			scheduler_agregar_evento(M_NPAQUETES, 0);
			//scheduler_agregar_evento(M_TESPERA, 0);
			break;
		}
		case M_NPAQUETES:{
			fila_logear_npaquetes(stdout, &fila);
			break;
		}
		case M_TESPERA:{
			break;
		}
		default:
			break;
		}

		//usleep(0);
	}

	FILE *fp = fopen("resultados_finales", "w");
	fila_logear_paquetes_peridos(fp, &fila);
	fila_logear_paquetes_consumidos(fp, &fila);
	fclose(fp);

	return 0;
}