#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 15 10:40:51 2017

@author: dfl1826a
"""

import numpy.random as loi
import matplotlib.pyplot as plt

X = loi.uniform(0, 9, 20)
Y = loi.uniform(0, 9, 20)

plt.figure()
    
plt.plot(X,Y,'xk')
plt.title('Croix noire des terres brûlées de Marchesang')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.show()