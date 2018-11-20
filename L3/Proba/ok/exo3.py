import numpy as np
import numpy.random as loi
import scipy.stats as loiT

X = loi.normal(0, 1, size=1000)
Y = loi.uniform(10, 20, size=1000)
Z = loi.uniform(0, 1, size=1000)

print("Covariance X et Y: ", np.cov(X,Y)[0,1])
print("Covariance X et Z: ", np.cov(X,Z)[0,1])
print("Covariance Y et Z: ", np.cov(Y,Z)[0,1])

