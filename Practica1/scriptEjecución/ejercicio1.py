#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@author: Antonio Jesús Heredia Castillo
"""

from matplotlib import pyplot as plt
import sys
import re
import numpy as np

if len(sys.argv) < 2:
  sys.exit("La ejecución debe ser: ejercicio1.py <nombreVentana> <datos1.txt> ... <datosN.txt>")

archivos = sys.argv

del archivos[0]

nombreVentana = archivos.pop(0)

for archivo in archivos:
  name = str(archivo)
  print("Leyendo el fichero de datos: "+name)
  f=open(name, "r")

  pos_inicial = []
  distancia = []
  for linea in f:
    coincidencias = re.findall(r"(media ([0-9]+(\.[0-9]+)*))", linea)
    if len(coincidencias) > 0:
      distancia.append(float(coincidencias[0][1]))
    
    coincidencias = re.findall(r"(Posicion inicial: \(([0-9]+(\.[0-9]+)*)\))", linea)
    if len(coincidencias) > 0:
      pos_inicial.append(int(coincidencias[0][1]))
  
  f.close()
  plt.plot(pos_inicial, distancia, label=name.split(".")[0])
  plt.xlabel('Posición inicial')
  plt.ylabel('Distancia media')

plt.legend()
plt.title(nombreVentana)  
plt.show()