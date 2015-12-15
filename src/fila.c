#include "fila.h"

int init_fila(struct fila_t *f){
	if(f == NULL)
		return -1;

	f->tamano           = K;
	f->paquetes_en_fila = 0;
	f->estado           = VACIA;
	f->paquetes_perdidos   = 0;
	f->paquetes_recibidos  = 0;
	f->paquetes_consumidos = 0;

	int i;
	for(i=0; i<K; i++){
		f->tiempos_espera[i] = 0.0;
	}

	return 0;
}

int fila_recibir_paquete(struct fila_t *f, double t_0){
	if(f == NULL)
		return -1;

	if(f->estado == LLENA){
		f->paquetes_perdidos++;
		return LLENA;
	}

	f->paquetes_en_fila++;
	f->paquetes_recibidos++;
	f->tiempos_espera[f->paquetes_en_fila-1] = t_0;
	
	if(f->paquetes_en_fila == f->tamano)
		f->estado = LLENA;

	if(f->estado == VACIA){
		f->estado = DISPONIBLE;
		return VACIA;
	}
	else
		return DISPONIBLE;
}

int fila_consumir_paquete(struct fila_t *f){
	if(f == NULL)
		return -1;

	if(f->estado == VACIA){
		return VACIA;
	}

	int i;
	for(i=1; i<=f->paquetes_en_fila; i++)
		f->tiempos_espera[i-1] = f->tiempos_espera[i];

	f->paquetes_en_fila--;
	f->paquetes_consumidos++;

	if(f->estado == LLENA)
		f->estado = DISPONIBLE;

	if(f->paquetes_en_fila == 0)
		f->estado = VACIA;
	else if(f->paquetes_en_fila < 0){
		f->paquetes_en_fila = 0;
		f->estado = VACIA;
	}

	return f->estado;
}

double fila_tiempo_paquete_a_consumir(struct fila_t *f){
	return f->tiempos_espera[0];
}

void fila_logear_npaquetes(FILE *fp, struct fila_t *f){
	if(fp == NULL)
		fprintf(stdout, "%d\n", f->paquetes_en_fila);
	else
		fprintf(fp, "%d\n", f->paquetes_en_fila);
}
void fila_logear_tiempo_paquete_consumido(FILE *fp, double t){
	if(fp == NULL)
		fprintf(stdout, "%f\n", t);
	else
		fprintf(fp, "%f\n", t);
}

void fila_logear_paquetes_peridos(FILE *fp, struct fila_t *f){
	if(fp == NULL)
		fprintf(stdout, "Perdidos : %ld\n", f->paquetes_perdidos);
	else
		fprintf(fp, "%ld\n", f->paquetes_perdidos);
}

void fila_logear_paquetes_consumidos(FILE *fp, struct fila_t *f){
	if(fp == NULL)
		fprintf(stdout, "Consumidos : %ld\n", f->paquetes_consumidos);
	else
		fprintf(fp, "%ld\n", f->paquetes_consumidos);
}