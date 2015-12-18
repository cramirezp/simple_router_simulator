#! /usr/bin/python
import subprocess
import math
import matplotlib
import matplotlib.pyplot as plt

t_simulacion = 1000000.0
K            = 11
#lrho         = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.95, 0.99]		# 0.99999 para 1
lrho         = [0.1]

### Resultados
if __name__=="__main__":
	for rho in lrho:
		print("\n*** Simulando p="+str(rho)+" ***")

		# correr simulador
		subprocess.call(["./bin/simulador", str(t_simulacion), str(rho), str(1)])

		# leer archivo de numero de paquetes
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

		# tiempo de espera medio
		ftespera = open("tespera_en_fila", "r")
		tesp  = []
		tespn = []
		with ftespera as l:
			tespn = l.readlines()
			for g in tespn:
				tesp.append( float(g.replace('\n', '')))
		tespera_medio = sum(tesp) / len(tesp)

		# Transientes
		f_tesp = []
		for i in range(1,len(tesp)/20):
			f_tesp.append(sum(tesp[0:i])/i)
		plt.stem(list(range(0,len(tesp)/20-1)), f_tesp)
		plt.show()

		### Valores teoricos
		p_n_T = [(1.0-rho)*(rho**n) / (1-rho**(K+1)) for n in range(0,K+1)]
		esperanza_n_T  = rho/(1-rho) - (K+1)*(rho**(K+1)) / (1-rho**(K+1))
		esperanza_nq_T = rho/(1-rho) - rho*(1+K*(rho**K)) / (1-rho**(K+1))
		tespera_medio_T  = esperanza_n_T / rho*(1-p_n_T[K]) #

		#print("Promedio   : " + str(promedio))
		#print("Desviacion : " + str(desviacion))
		print("N medio paqs en sis : " + "%.3f"%esperanza_n_T  + " -> obtenido : " + "%.3f"%esperanza_n + " .. diferencia :" +"%.5f"%(esperanza_n_T-esperanza_n))
		print("N medio paqs en fila: " + "%.3f"%(esperanza_nq_T) + " -> obtenido : " + "%.3f"%(esperanza_nq) + " .. diferencia :" +"%.5f"%(esperanza_nq_T-esperanza_nq))
		print("Tiempo medio de espera en fila : " + "%.3f"%tespera_medio_T + " -> obtenido : "  + "%.3f"%tespera_medio + " .. diferencia :" +"%.5f"%(tespera_medio_T-tespera_medio))
		for i in range(0,K+1):
			print("Probabilidad "+str(i)+" paqs : " + "%.3f"%(p_n_T[i]) + " -> obtenido : "+ "%.3f"%(p_n[i])  + " .. diferencia :" "%.5f"%(p_n_T[i]-p_n[i]))

