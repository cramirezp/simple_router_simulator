#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lcgrand.h"

#include "lista.h"

#define O_RESOLUTION 0.1
#define MAX_ACUM_VALUE 1-0.01

double iacum_exp(double F, double lambda);

int main(int argc, char **argv){
	FILE *fp = NULL, *fp2 = NULL;

	/* Variable aleatoria exponencial */
	double lambda = 0.1;						// parametro lambda
	if(argc >1) lambda  = atof(argv[1]);

	double o_resolution = O_RESOLUTION;
	if(argc >2) o_resolution = atof(argv[2]);
	
	struct lista_acum lista;
	lista_init(&lista);

	double i;
	fp = fopen("dis_exponencial", "w");
	fp2 = fopen("acum_exponencial", "w");
	for(i=0.0; iacum_exp( i, lambda)< MAX_ACUM_VALUE; i+=o_resolution){
		fprintf(fp, "%f\n", lambda*exp( -lambda*i));
		fprintf(fp2, "%f\n", iacum_exp( i, lambda));
		lista_agregar(&lista, i, iacum_exp( i, lambda));
	}
	fclose(fp);
	fclose(fp2);

	lcgrandst(1, 0);
	double r = 0.0;

	fp  = fopen("acum_exponencial_calc", "w");
	const int n_points = 1000;
	for(i=0; i<n_points; i++){
		lista_reiniciar(&lista);
		r = lcgrand(0);

		while(lista.actual->acumulada < r && lista_siguiente(&lista));

		if(lista.actual == NULL)
			continue;

		fprintf(fp, "%f\n", lista.actual->x);		
	}
	fclose(fp);

	return 0;
}

double iacum_exp(double F, double lambda){
	return 1-exp(-lambda*F);
}