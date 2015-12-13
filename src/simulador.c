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

#define N_EVENTOS 10000000L			// -1 maxima espera.  Tanto eventos de FILA como de MEDICION

#define LAMBDA 	0.1
#define MU 		1

#define SEED0	1
#define SEED1	53

int main(int argc, char *argv[]){
	if(init_scheduler()){
		printf("Error inicializacion scheduler\n");
		return 1;
	}

	struct fila_t fila;
	if(init_fila(&fila) <0){
		printf("Error inicializacion fila\n");
		return 2;
	}

	double t_arribo  = iacum_exp(lcgrand(SEED0), LAMBDA);
	double t_consumo = iacum_exp(lcgrand(SEED1), MU) + t_arribo;
	scheduler_agregar_evento(ARRIBO, t_arribo);
	scheduler_agregar_evento(CONSUMO, t_consumo);

	FILE *fpf = fopen("npaq_en_fila", "w");

	for(unsigned long i=0; hay_evento() && i < N_EVENTOS; i++){
		consumir_evento();

		switch(ultimo_evento()){
		case ARRIBO:{
			fila_recibir_paquete(&fila);
			
			scheduler_agregar_evento(ARRIBO, iacum_exp(lcgrand(SEED0), LAMBDA));
			scheduler_agregar_evento(M_NPAQUETES, 0);
			break;
		}
		case CONSUMO:{
			fila_consumir_paquete(&fila);
			
			scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(SEED1), MU));
			scheduler_agregar_evento(M_NPAQUETES, 0);
			//scheduler_agregar_evento(M_TESPERA, 0);
			break;
		}
		case M_NPAQUETES:{
			fila_logear_npaquetes(fpf, &fila);
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

	FILE *fpe = fopen("resultados_finales", "w");
	fila_logear_paquetes_peridos(fpe, &fila);
	fila_logear_paquetes_consumidos(fpe, &fila);

	fclose(fpf);
	fclose(fpe);

	return 0;
}