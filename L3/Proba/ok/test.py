import numpy as np
import numpy.random as loi
import scipy.stats as loiT
import matplotlib.pyplot as plt

def ligne_regression(bornInf, bornSup, taille):
    
    x = loi.uniform(bornInf,bornSup,taille)
    y = loi.uniform(bornInf,bornSup,taille)
    
    return (x,y)
    

x, y = ligne_regression(0,9,10)
mX = np.mean(x)
mY = np.mean(y)
varX = np.var(x)
covXY = np.cov(x,y)[0,1]
Y = (covXY/varX)*(x-mX)+mY

plt.figure()
plt.plot(x, y, 'xk')
plt.plot(x, Y, 'r')
plt.title('Ligne de regression - 10')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.show()

x, y = ligne_regression(0,9,100)
mX = np.mean(x)
mY = np.mean(y)
varX = np.var(x)
covXY = np.cov(x,y)[0,1]
Y = (covXY/varX)*(x-mX)+mY

plt.figure()
plt.plot(x, y, 'xk')
plt.plot(x, Y, 'r')
plt.title('Ligne de regression - 100')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.show()

x, y = ligne_regression(0,9,1000)
mX = np.mean(x)
mY = np.mean(y)
varX = np.var(x)
covXY = np.cov(x,y)[0,1]
Y = (covXY/varX)*(x-mX)+mY

plt.figure()
plt.plot(x, y, 'xk')
plt.plot(x, Y, 'r')
plt.title('Ligne de regression - 1000')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.show()
