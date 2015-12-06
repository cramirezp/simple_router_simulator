#! /usr/bin/python
import matplotlib
import matplotlib.pyplot as plt


farribo = open("arribos", "r")

f  = []
fn = []

with farribo as l:
	fn = l.readlines()
	for g in fn:
		f.append( float(g.replace('\n', '')))

t  = 0
ff = []
for x in f:
	ff.append(x-t)
	t = x


promedio = sum( ff ) / len(ff)
varianza = sum( [(x-promedio)**2 for x in ff] ) / len(ff)

print("Promedio : " + str(promedio))
print("Varianza : " + str(varianza))

#plt.stem(list(range(0,len(f))), ff)
#plt.show()
