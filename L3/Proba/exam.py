#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 19 11:06:35 2017

@author: dfl1826a
"""

import matplotlib.pyplot as plt
import numpy.random as loi
import numpy as np
import scipy.stats as loiT

X1 = loi.uniform(0, 1, 100)
X2 = -(np.log(X1))

plt.figure()
plt.hist(X1, 20, normed=True, label='resultat pratique')
plt.title('Loi uniforme')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()
    
m1 = np.mean(X1)
m2 = np.mean(X2)

e1 = np.var(X1)
e1 = np.sqrt(e1)
e2 = np.var(X2)
e2 = np.sqrt(e2)

print("moyenne X1, X2: ", m1, m2)
print("ecart type X1, X2: ", e1, e2)
print("covariance X1, X2: ", np.cov(X1,X2)[0,1])
print("correlation X1, X2: ", np.corrcoef(X1,X2)[0,1])


slope, intercept, r_value, p_value, std_err = loiT.linregress(X1,X2)
fitLine = slope * X1 + intercept

print("a, b: ", slope, intercept)
plt.figure()
plt.plot(X1, X2, 'xk')
plt.plot(X1,fitLine,'r')
plt.title('Loi uniforme')
plt.xlabel('X1')
plt.ylabel('X2')
plt.legend()
plt.show()
