#! /usr/bin/python
import math
import matplotlib
import matplotlib.pyplot as plt

K   = 10
rho = 1


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


promedio = sum( f ) / len(f)
desviacion = math.sqrt(sum( [(x-promedio)**2 for x in f] ) / len(f))


p_n = [len([x for x in f if x==n_paqs])*1.0 / len(f) for n_paqs in range(0,K+1)]
#esperanza_n  = p_n/(1-p_n) - (K+1)*p_n**(K+1) / (1-p_n**(K+1))
#esperanza_nq = p_n/(1-p_n) - p*(1+K*p**K) / (1-p_n**(K+1))
#esperanza_w  = esperanza_nq / lambda(1-p_K)

print("Promedio   : " + str(promedio))
print("Desviacion : " + str(desviacion))
print("Probabilidad 0 paqs : " + str(p_n[0]))
