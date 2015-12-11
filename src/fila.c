#include "fila.h"

int init_fila(struct fila_t *f){
	if(f == NULL)
		return 1;

	f->tamano           = K;
	f->paquetes_en_fila = 0;
	f->estado           = VACIA;
	f->paquetes_perdidos   = 0;
	f->paquetes_recibidos  = 0;
	f->paquetes_consumidos = 0;

	return 0;
}

int fila_recibir_paquete(struct fila_t *f){
	if(f == NULL)
		return -1;

	if(f->estado == BLOQUEADA){
		f->paquetes_perdidos++;
		return 0;
	}
	else{
		f->paquetes_en_fila++;
		f->paquetes_recibidos++;
		if(f->paquetes_en_fila == f->tamano){
			f->estado = BLOQUEADA;
		}
	}

	return 1;
}

int fila_consumir_paquete(struct fila_t *f){
	if(f == NULL)
		return -1;

	if(f->estado == VACIA){
		return 0;
	}

	f->paquetes_en_fila--;
	f->paquetes_consumidos++;
	if(f->estado == BLOQUEADA)
		f->estado = DISPONIBLE;
	if(f->paquetes_en_fila == 0)
		f->estado = VACIA;

	return 1;
}

void fila_logear_npaquetes(FILE *fp, struct fila_t *f){
	if(fp == NULL)
		fprintf(stdout, "%d\n", f->paquetes_en_fila);
	else
		fprintf(fp, "%d\n", f->paquetes_en_fila);
}

void fila_logear_paquetes_peridos(FILE *fp, struct fila_t *f){
	if(fp == NULL)
		fprintf(stdout, "%ld\n", f->paquetes_perdidos);
	else
		fprintf(fp, "%ld\n", f->paquetes_perdidos);
}

void fila_logear_paquetes_consumidos(FILE *fp, struct fila_t *f){
	if(fp == NULL)
		fprintf(stdout, "%ld\n", f->paquetes_consumidos);
	else
		fprintf(fp, "%ld\n", f->paquetes_consumidos);
}