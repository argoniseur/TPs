import numpy as np
import numpy.random as loi
import scipy.stats as loiT
import matplotlib.pyplot as plt

nbVal = 10
intervalle = 0.2
x = loi.uniform(0,1,nbVal)
vec = np.arange(0,1.2,intervalle)

print(vec)


def chi2(loiu, mean):
	ret = 0
	for i in loiu:
		ret = ret+(np.power((i-mean), 2)/mean)
	
	return ret

chi2calc = chi2(x,nbVal*intervalle)
print(chi2calc)
# r = k-s avec k = nbbarres et s nbcontraintes
r = 5-1
print(1-loiT.chi2.cdf(chi2calc, r))

plt.figure()
plt.hist(x, bins=vec)
plt.title('exo 6')
plt.xlabel('Intervalle')
plt.ylabel('Nb occurences')
plt.legend()
plt.show()

# plus la valeur est proche de 1, plus l'hypothèse comme quoi x est une loi uniforme est vérifié
