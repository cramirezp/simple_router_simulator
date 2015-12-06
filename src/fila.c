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
		return 1;

	if(f->estado == BLOQUEADA){
		f->paquetes_perdidos++;
		return 2;
	}
	else{
		f->paquetes_en_fila++;
		f->paquetes_recibidos++;
		if(f->paquetes_en_fila == f->tamano){
			f->estado = BLOQUEADA;
		}
	}

	return 0;
}

int fila_consumir_paquete(struct fila_t *f){
	if(f == NULL)
		return 1;

	if(f->estado == VACIA){
		return 2;
	}

	f->paquetes_en_fila--;
	f->paquetes_consumidos++;
	if(f->paquetes_en_fila == 0)
		f->estado = VACIA;

	return 0;
}

void fila_imprimir(struct fila_t *f){
	printf("%d\n", f->paquetes_en_fila);
}