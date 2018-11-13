#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import numpy as np
import matplotlib.pyplot as plt

a = np.array([1,4,2,9,14,3,16])
print("Mat: ", a);

a = np.array([6,2,15,8,24,7])
a = a.reshape(6,1)
print("Mat:\n", a);

a = np.mat([[1,4,5,7],[5,7,3,11],[18,4,9,2]])
print("Mat:\n", a)

a = np.arange(3,21,0.5)
print("Mat:\n", a)

a = np.eye(3)
print("Mat:\n", a*4)

a = np.eye(3)*2
b = np.mat([[1,1],[1,1],[0,0]])
c = np.concatenate((a,b), axis=1)
print("Mat:\n", c)

#B = np.random.random_integers(0, 20, (3, 5))
#C = np.random.random_integers(0, 20, (3, 5))
B = np.random.rand(3,5)
C = np.random.rand(3,5)
print("B:\n", B, "\nC:\n", C)
F = B*C
print("F:\n", F)
G = np.dot(B,np.transpose(C))
print("G:\n", G)

print("\n", F[(F>0.2) & (F<0.6)])
print("\n", G[G>=0.6])
