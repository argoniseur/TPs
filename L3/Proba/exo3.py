#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 15 10:40:51 2017

@author: dfl1826a
"""

import numpy as np
import numpy.random as loi

X = loi.normal(0, 1, size=1000)
Y = loi.uniform(10, 20, size=1000)
Z = loi.uniform(0, 1, size=1000)

print("Covariance X et Y: ", np.cov(X,Y)[0,1])
print("Covariance X et Z: ", np.cov(X,Z)[0,1])
print("Covariance Y et Y: ", np.cov(Y,Z)[0,1])
print("Seule la valeur 2 ou 3 de la matrice nous intéresse (elles sont similaires), la fonction cov calculant toutes les valeurs de covariance possible avec X et Y, soit X,X, X,Y, Y,X et Y,Y")
print("Les valeurs de covariance sont faibles car plus elles sont faibles, plus les variables aléatoires sont indépendantes")
