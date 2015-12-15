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

#define LAMBDA 	0.99
#define MU 		1

#define SEED0	1
#define SEED1	53

int main(int argc, char *argv[]){
	float lambda=LAMBDA, mu=MU;
	if(argc > 1)
		lambda = atof(argv[1]);
	if(argc > 2)
		mu     = atof(argv[2]);

	if(init_scheduler()){
		printf("Error inicializacion scheduler\n");
		return 1;
	}

	struct fila_t fila;
	if(init_fila(&fila) <0){
		printf("Error inicializacion fila\n");
		return 2;
	}
	
	// Inicio de simulacion
	double t_sim = 0.0;
	scheduler_agregar_evento(ARRIBO,  t_sim + iacum_exp(lcgrand(SEED0), lambda));
	scheduler_agregar_evento(CONSUMO, t_sim + iacum_exp(lcgrand(SEED1), mu));

	FILE *fpf = fopen("npaq_en_fila", "w");
	FILE *fpt = fopen("tespera_en_fila", "w");
	for(unsigned long i=0; hay_evento() && i < N_EVENTOS; i++){
		consumir_evento(&t_sim);

		switch(ultimo_evento()){
		case ARRIBO:{
			double t_paquete =  t_sim + iacum_exp(lcgrand(SEED0), lambda);
			
			fila_recibir_paquete(&fila, t_paquete);

			fila_logear_npaquetes(fpf, &fila);

			scheduler_agregar_evento(ARRIBO, t_paquete);
			break;
		}
		case CONSUMO:{
			fila_logear_tiempo_paquete_consumido(stdout, t_sim - fila_tiempo_paquete_a_consumir(&fila));

			fila_consumir_paquete(&fila);
			
			fila_logear_npaquetes(fpf, &fila);

			scheduler_agregar_evento(CONSUMO, t_sim + iacum_exp(lcgrand(SEED1), mu));
			break;
		}
		case M_NPAQUETES:{
			//fila_logear_npaquetes(fpf, &fila);
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
	fclose(fpf);
	fclose(fpt);

	FILE *fpe = fopen("resultados_finales", "w");
	fila_logear_paquetes_peridos(fpe, &fila);
	fila_logear_paquetes_consumidos(fpe, &fila);
	fclose(fpe);

	return 0;
}