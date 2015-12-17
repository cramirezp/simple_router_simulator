#include <stdio.h>

#define K 11		// Tamaño de sistema

enum ESTADO_FILA{DISPONIBLE, VACIA, LLENA};

struct fila_t{
	// Estado
	int tamano;
	int paquetes_en_fila;
	double tiempos_entrada[K];
	enum ESTADO_FILA estado;
	double tiempo_ultimo_paquete;
	// Datos generales
	long paquetes_perdidos;
	long paquetes_recibidos;
	long paquetes_consumidos;
};

int init_fila(struct fila_t *f);
int fila_recibir_paquete(struct fila_t *f, double t_0);
int fila_consumir_paquete(struct fila_t *f);
double fila_tiempo_paquete_a_consumir(struct fila_t *f);

void fila_logear_npaquetes(FILE *fp, struct fila_t *f);
void fila_logear_paquetes_peridos(FILE *fp, struct fila_t *f);
void fila_logear_paquetes_consumidos(FILE *fp, struct fila_t *f);
void fila_logear_tiempo_paquete_consumido(FILE *fp, struct fila_t *f, double tiempo_actual);
