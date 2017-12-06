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

x1=X
x2=X+Y

y1=X
y2=X*Y

z1=2*X+Y
z2=3*X+Y

print("Coefficient de correlation x1 et x2: ", np.corrcoef(x1,x2)[0,1])
print("Coefficient de correlation y1 et y2: ", np.corrcoef(y1,y2)[0,1])
print("Coefficient de correlation z1 et z2: ", np.corrcoef(z1,z2)[0,1])

print("x1 et x2 sont peu correlés au contraire des deux autres cas")