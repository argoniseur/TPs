import numpy as np
import numpy.random as loi
import scipy.stats as loiT
import matplotlib.pyplot as plt

x = loi.uniform(0,1,10)
vec = np.arange(0,1.2,0.2)

print(vec)
plt.figure()
plt.hist(x, bins=vec)
plt.title('exo 6')
plt.xlabel('Intervalle')
plt.ylabel('Nb occurences')
plt.legend()
plt.show()

def chi2
