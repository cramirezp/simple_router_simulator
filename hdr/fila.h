#include <stdio.h>

#define K 10		// Tamaño fila

enum ESTADO_FILA{DISPONIBLE, VACIA, BLOQUEADA};

struct fila_t{
	// Estado
	int tamano;
	int paquetes_en_fila;
	enum ESTADO_FILA estado;
	// Datos generales
	long paquetes_perdidos;
	long paquetes_recibidos;
	long paquetes_consumidos;
};

int init_fila(struct fila_t *f);
int fila_recibir_paquete(struct fila_t *f);
int fila_consumir_paquete(struct fila_t *f);
void fila_imprimir(struct fila_t *f);