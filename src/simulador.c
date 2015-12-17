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

#define T_SIM 1000000.0			// Tiempo de simulacion. Inversa de la magnitud de los parametros son la escala

#define LAMBDA 	0.99
#define MU 		1

#define ISEED0	1
#define ISEED1	53

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
	scheduler_agregar_evento(ARRIBO , iacum_exp(lcgrand(ISEED0), lambda));
	scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(ISEED1), mu));

	FILE *fpf = fopen("npaq_en_fila", "w");
	FILE *fpt = fopen("tespera_en_fila", "w");
	while(tiempo_simulacion() < T_SIM){
		if(!hay_evento())
			return 1;	// error

		scheduler_consumir_evento();

		switch(evento_actual()){
		case ARRIBO:{
			fila_recibir_paquete(&fila, tiempo_simulacion());
			fila_logear_npaquetes(fpf, &fila);

			scheduler_agregar_evento(ARRIBO, iacum_exp(lcgrand(ISEED0), lambda));
			break;
		}
		case CONSUMO:{
			fila_consumir_paquete(&fila);
			fila_logear_npaquetes(fpf, &fila);

			scheduler_agregar_evento(CONSUMO, iacum_exp(lcgrand(ISEED1), mu));
			break;
		}
		default:
			break;
		}
	}
	fclose(fpf);
	fclose(fpt);

	FILE *fpe = fopen("resultados_finales", "w");
	fclose(fpe);

	return 0;
}