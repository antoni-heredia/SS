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
    coincidencias = re.findall(r"(s:([0-9]+(\.[0-9]+)*))", linea)
    if len(coincidencias) > 0:
      print(coincidencias)
      distancia.append(float(coincidencias[0][1]))
    
    coincidencias = re.findall(r"(ganacia:(-?[0-9]+(\.[0-9]+)*))", linea)
    if len(coincidencias) > 0:
      print(coincidencias)
      pos_inicial.append(float(coincidencias[0][1]))
  
  f.close()
  plt.plot(distancia,pos_inicial , label=name.split(".")[0])
  plt.xlabel('Cantidad pedida')
  plt.ylabel('Ganancia')

plt.legend()
plt.title(nombreVentana)  
plt.show()