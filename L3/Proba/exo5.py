import numpy as np
import numpy.random as loi
import scipy.stats as loiT
import matplotlib.pyplot as plt

def ligne_regression(bornInf, bornSup, taille):
    
    x = loi.uniform(bornInf,bornSup,taille)
    y = loi.uniform(bornInf,bornSup,taille)
    
    return (x,y)
    

# DEBUT DU PROGRAMME PRINCIPAL
    
x, y = ligne_regression(0,9,10)

slope, intercept, r_value, p_value, std_err = loiT.linregress(x,y)
fitLine = slope * x + intercept

plt.figure()
plt.plot(x, y, 'xk')
plt.plot(x,fitLine,'r')
plt.title('Loi uniforme')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.show()

x, y = ligne_regression(0,9,100)

slope, intercept, r_value, p_value, std_err = loiT.linregress(x,y)
fitLine = slope * x + intercept

plt.figure()
plt.plot(x, y, 'xk')
plt.plot(x,fitLine,'r')
plt.title('Loi uniforme')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.show()

x, y = ligne_regression(0,9,1000)

slope, intercept, r_value, p_value, std_err = loiT.linregress(x,y)
fitLine = slope * x + intercept

plt.figure()
plt.plot(x, y, 'xk')
plt.plot(x,fitLine,'r')
plt.title('Loi uniforme')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.show()

