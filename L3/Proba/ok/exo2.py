import numpy as np
import numpy.random as loi
import scipy.stats as loiT



x1 = loi.uniform(10, 20, size=1000)
x2 = loi.uniform(10, 20, size=10000)
x3 = loi.uniform(10, 20, size=100000)

e1 = np.mean(x1)
e2 = np.mean(x2)
e3 = np.mean(x3)

v1 = np.var(x1)
v2 = np.var(x2)
v3 = np.var(x3)

print("Esperance x1, x2, x3: ", e1, e2, e3)
print("Variance x1, x2, x3: ", v1, v2, v3)

vec = np.arange(10, 20, 0.02)
xt = loiT.uniform.pdf(vec, 10, 10)
print("Esperance: ", 100/12, " Variance: ", 15, "\n\n")


x1 = loi.normal(0, 1, size=1000)
x2 = loi.normal(0, 1, size=10000)
x3 = loi.normal(0, 1, size=100000)

e1 = np.mean(x1)
e2 = np.mean(x2)
e3 = np.mean(x3)

v1 = np.var(x1)
v2 = np.var(x2)
v3 = np.var(x3)

print("Esperance x1, x2, x3: ", e1, e2, e3)
print("Variance x1, x2, x3: ", v1, v2, v3)

vec = np.arange(0, 1, 0.02)
xt = loiT.uniform.pdf(vec, 0, 1)
print("Esperance: ", 0, " Variance: ", 1, "\n\n")


x1 = loi.exponential(1/0.5, size=1000)
x2 = loi.exponential(1/0.5, size=10000)
x3 = loi.exponential(1/0.5, size=100000)

e1 = np.mean(x1)
e2 = np.mean(x2)
e3 = np.mean(x3)

v1 = np.var(x1)
v2 = np.var(x2)
v3 = np.var(x3)

print("Esperance x1, x2, x3: ", e1, e2, e3)
print("Variance x1, x2, x3: ", v1, v2, v3)

vec = np.arange(0, 1, 0.02)
xt = loiT.expon.pdf(vec, loc=0, scale=1/0.5)
print("Esperance: ", 1/0.5, " Variance: ", 1/0.25, "\n\n")

print("Les valeurs réelles et théoriques sont très proches les unes des autres. Le tirage réel permet donc de valider la loi théorique")
print("Plus le nombre de tirage est important, plus les valeurs sont proches de la valeur théorique")
