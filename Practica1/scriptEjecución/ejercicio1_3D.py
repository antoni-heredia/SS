#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@author: Antonio Jesús Heredia Castillo
"""

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys
import re
import numpy as np

if len(sys.argv) < 2:
  sys.exit("La ejecución debe ser: ejercicio1.py <nombreVentana> <datos1.txt> ... <datosN.txt>")

archivos = sys.argv

del archivos[0]

nombreVentana = archivos.pop(0)
fig = plt.figure()
ax = plt.axes(projection='3d')
pos_inicial = []
distancia = []
variable = []
for archivo in archivos:
  name = str(archivo)
  print("Leyendo el fichero de datos: "+name)
  f=open(name, "r")

  
  primera = True
  for linea in f:
    if primera:
      primera = False
      variable.append(float(linea))

    if "Mejor distancia" in linea:
      distancia.append(float(linea.split(":")[1]))
    if "Mejor posicion inicial" in linea:
      pos_inicial.append(float(linea.split(":")[1]))

  f.close()
ax.plot(variable,pos_inicial ,distancia,label=name.split(".")[0])
ax.set_ylabel('Mejor posicion')
ax.set_zlabel('Mejor distancia')
ax.set_xlabel('Probabilidad')

ax
ax.set_title(nombreVentana)  
plt.show()
