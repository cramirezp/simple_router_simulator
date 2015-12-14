#! /usr/bin/python
import math
import matplotlib
import matplotlib.pyplot as plt

K   = 11
rho = 0.99		# 0.99999 para 1


farribo = open("npaq_en_fila", "r")

f  = []
fn = []

with farribo as l:
	fn = l.readlines()
	for g in fn:
		f.append( float(g.replace('\n', '')))

farribo.close();

t  = 0
ff = []
for x in f:
	ff.append(x-t)
	t = x

### Valores obtenidos por la simulacion

promedio = sum( f ) / len(f)
desviacion = math.sqrt(sum( [(x-promedio)**2 for x in f] ) / len(f))

p_n = [len([x for x in f if x==n_paqs])*1.0 / len(f) for n_paqs in range(0,K+1)]

esperanza_n  = promedio
esperanza_nq = sum([x*p_n[x+1] for x in range(1,K)])


### Valores teoricos
p_n_T = [(1.0-rho)*(rho**n) / (1-rho**(K+1)) for n in range(0,K+1)]
esperanza_n_T  = rho/(1-rho) - (K+1)*(rho**(K+1)) / (1-rho**(K+1))
esperanza_nq_T = rho/(1-rho) - rho*(1+K*(rho**K)) / (1-rho**(K+1))
#esperanza_w  = esperanza_nq / lambda(1-p_K)

### Resultados
if __name__=="__main__":
	#print("Promedio   : " + str(promedio))
	#print("Desviacion : " + str(desviacion))
	print("N medio paqs en sis : " + str(esperanza_n_T)  + " -> obtenido : " + str(esperanza_n))
	print("N medio paqs en fila: " + str(esperanza_nq_T) + " -> obtenido : " + str(esperanza_nq))
	for i in range(0,K+1):
		print("Probabilidad "+str(i)+" paqs : " + str(p_n_T[i]) + " -> obtenido : "+ str(p_n[i]))
