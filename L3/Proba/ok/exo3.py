import numpy as np
import numpy.random as loi
import scipy.stats as loiT

X = loi.normal(0, 1, size=1000)
Y = loi.uniform(10, 20, size=1000)
Z = loi.uniform(0, 1, size=1000)

print("Covariance X et Y: ", np.cov(X,Y)[0,1])
print("Covariance X et Z: ", np.cov(X,Z)[0,1])
print("Covariance Y et Z: ", np.cov(Y,Z)[0,1])

print("Seules les valeurs en [0,1] ou [1,0] nous intéressent car np.cov(X,Y) calcule toutes les valeurs de covariance possible X,X X,Y Y,X Y,Y")
print("Plus une valeur de covariance est faible, moins les variables aléatoires sont corrélées. Ici, les valeurs faiblent indiquent donc que les variables sont indépendantes")
