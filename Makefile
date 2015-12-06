### Directorios #################################
IDIR = hdr
SDIR = src
ODIR = obj
BDIR = bin

### Comipilador #################################
CC     = gcc
CFLAGS = -Wall -std=gnu99 -I$(IDIR)/

LIBS = -lm 


### Instrucciones de compilacion ################
all: simulador
build: clean simulador
run:
	@$(BDIR)/./simulador


simulador: lcgrand.o simulador.o
	@$(CC) -o $(BDIR)/simulador $(ODIR)/simulador.o $(ODIR)/lcgrand.o $(LIBS)

%.o:  $(SDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $(ODIR)/$@

# limpieza
clean: clean_obj clean_bin

clean_obj:
	@rm -f $(ODIR)/*.o

clean_bin:
	@rm -f $(BDIR)/*

