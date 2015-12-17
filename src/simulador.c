/*************************************************************************
* Simulador router con una fila de espera.
* Arribo y consumo son V.A. exponenciales de parametros lambda y mu.
*
***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lcgrand.h"
#include "scheduler.h"
#include "exponencial.h"
#include "fila.h"

#define T_SIM 10000000.0			// -1 maxima espera.  Tanto eventos de FILA como de MEDICION

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

	if(scheduler_inicializar()){
		printf("Error inicializacion scheduler\n");
		return 1;
	}

	struct fila_t fila;
	if(init_fila(&fila) <0){
		printf("Error inicializacion fila\n");
		return 2;
	}
	
	// Arranque de simulacion
	scheduler_agregar_evento(ARRIBO , iacum_exp(lcgrand(SEED0), lambda));
	scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(SEED1), mu));

	scheduler_imprimir();

	FILE *fpf = fopen("npaq_en_fila", "w");
	FILE *fpt = fopen("tespera_en_fila", "w");
	while(hay_evento() && tiempo_simulacion() < T_SIM){
		scheduler_consumir_evento();

		switch(evento_actual()){
		case ARRIBO:{
			printf("Arribo  : %.2f\n", tiempo_simulacion());
			scheduler_agregar_evento(ARRIBO, iacum_exp(lcgrand(SEED0), lambda));
			break;
		}
		case CONSUMO:{
			printf("Consumo : %.2f\n", tiempo_simulacion());
			scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(SEED1), mu));
			break;
		}
		default:
			break;
		}
		scheduler_imprimir();
		usleep(5000);
	}
	fclose(fpf);
	fclose(fpt);

	FILE *fpe = fopen("resultados_finales", "w");
	fclose(fpe);

	return 0;
}