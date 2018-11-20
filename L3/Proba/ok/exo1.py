import numpy as np
import matplotlib.pyplot as plt
import numpy.random as loi
import scipy.stats as loiT

a = np.array([1,4,2,9,14,3,16])
print("Mat: ", a);

a = np.array([6,2,15,8,24,7])
a = a.reshape(6,1)
print("Mat:\n", a);

a = np.mat([[1,4,5,7],[5,7,3,11],[18,4,9,2]])
print("Mat:\n", a)

a = np.arange(3,21,0.5)
print("Mat:\n", a)

a = np.eye(3)
print("Mat:\n", a*4)

a = np.eye(3)*2
b = np.mat([[1,1],[1,1],[0,0]])
c = np.concatenate((a,b), axis=1)
print("Mat:\n", c)

#B = np.random.random_integers(0, 20, (3, 5))
#C = np.random.random_integers(0, 20, (3, 5))
B = np.random.rand(3,5)
C = np.random.rand(3,5)
print("B:\n", B, "\nC:\n", C)
F = B*C
print("F:\n", F)
G = np.dot(B,np.transpose(C))
print("G:\n", G)

print("\n", F[(F>0.2) & (F<0.6)])
print("\n", G[G>=0.6])

x = np.arange(-1,5,0.1)
x1 = loiT.norm.pdf(x,2,1)
# Affichage des points relies entre eux
plt.figure()
plt.plot(x, x1)
plt.xlabel('axe des abcisses')
plt.ylabel('axe desordonne')
plt.show()

# Affiche la courbe
x = np.arange(0,10,0.1)
x1 = loiT.norm.pdf(x,5,3)
x2 = loiT.expon.pdf(x)

plt.figure()
plt.plot(x, x1)
plt.plot(x, x2)
plt.xlabel('axe des abcisses')
plt.ylabel('axe desordonne')
plt.show()

x2 = loi.normal(5,1,size=1000)
plt.figure()
plt.hist(x2, 20)
plt.xlabel('axe des abcisses')
plt.ylabel('axe desordonne')
plt.show()

def loi_unif(nb_val, a, b, barres, pas): 

    # Loi pratique (valeurs aleatoires)
    xp = loi.uniform(a, b, size=nb_val)

    # Normalisation
    mini = a
    maxi = b

    # Loi theorique
    vec = np.arange(mini, maxi, pas)
    xt = loiT.uniform.pdf(vec, loc=a, scale=b-a)
    
    # Affichage
    plt.figure()
    plt.hist(xp, barres, normed=True, label='resultat pratique')
    plt.plot(vec, xt, 'r', label='resultat theorique') # A MODIFIER dans le cas discret par 'or'
    plt.title('Loi uniforme')
    plt.xlabel('Intervalles')
    plt.ylabel('Probabilites')
    plt.legend()
    plt.show()

# Loi exponnentielle
def loi_exp(nb_val, l, barres, pas): # A COMPLETER...

    # Loi pratique (valeurs aleatoires)
    xp = loi.exponential(1/l, size=nb_val)
    
    # Normalisation
    mini = np.min(xp)
    maxi = np.max(xp)

    # Loi theorique
    vec = np.arange(mini, maxi, pas)
    xt = loiT.expon.pdf(vec, loc=0, scale=1/l)

    # Affichage
    plt.figure()
    plt.hist(xp, barres, normed=True, label='resultat pratique')
    plt.plot(vec, xt, 'r', label='resultat theorique') # A MODIFIER dans le cas discret par 'or'
    plt.title('Loi exponentielle')
    plt.xlabel('Intervalles')
    plt.ylabel('Probabilites')
    plt.legend()
    plt.show()
    
# Loi geometrique
def loi_geo(nb_val, p, barres, pas):

    # Loi pratique (valeurs aleatoires)
    xp = loi.geometric(p, size=nb_val)

    # Normalisation
    mini = np.min(xp)
    maxi = np.max(xp)

    # Loi theorique
    vec = np.arange(mini, maxi, pas)
    xt = loiT.geom.pmf(vec,p)

    # Affichage
    plt.figure()
    plt.hist(xp, barres, normed=True, label='resultat pratique')
    plt.plot(vec, xt, 'or', label='resultat theorique') # A MODIFIER dans le cas discret par 'or'
    plt.title('Loi géométrique')
    plt.xlabel('Intervalles')
    plt.ylabel('Probabilites')
    plt.legend()
    plt.show()

# Loi de Poisson
def loi_poisson(nb_val, l, barres, pas):

    # Loi pratique (valeurs aleatoires)
    xp = loi.poisson(l, size=nb_val)

    # Normalisation
    mini = np.min(xp)
    maxi = np.max(xp)

    # Loi theorique
    vec = np.arange(mini, maxi, pas)
    xt = loiT.poisson.pmf(vec,l)

    # Affichage
    plt.figure()
    plt.hist(xp, barres, normed=True, label='resultat pratique')
    plt.plot(vec, xt, 'or', label='resultat theorique') # A MODIFIER dans le cas discret par 'or'
    plt.title('Loi de Poisson')
    plt.xlabel('Intervalles')
    plt.ylabel('Probabilites')
    plt.legend()
    plt.show()
    
# Loi Normale
def loi_normale(nb_val, esperance, ecart_type, barres, pas):
   
    #Loi pratique (valeurs aleatoires)
    xp = loi.normal(esperance, ecart_type, size=nb_val)
    
    #Normalisation
    mini = np.min(xp)
    maxi = np.max(xp)
    
    # Loi Theorique

    vec = np.arange(mini, maxi, pas)
    xt = loiT.norm.pdf(vec,esperance,ecart_type)
    
    #Affichage
    plt.figure()
    plt.hist(xp, barres, normed=True, label='resusltat pratique')
    plt.plot(vec, xt, 'r', label='resultat theorique')
    plt.title('Loi Normale')
    plt.xlabel('Intervalles')
    plt.ylabel('Probabilites')
    plt.legend()
    plt.show()
   
# DEBUT DU PROGRAMME PRINCIPAL

# Constante
nb_barres = 20
pas_reel = 0.02
pas_discret = 1

# (a) Tests de la loi Uniforme : loi reelle
# 50 valeurs suivant une loi uniforme (min=0 & max=20)
loi_unif(50, 0, 20, nb_barres, pas_reel)
# 10000 valeurs suivant une loi uniforme (min=0 & max=20)
loi_unif(10000, 0, 20, nb_barres, pas_reel)
# 10000 valeurs suivant une loi uniforme (min=-5 & max=5)
loi_unif(10000, -5, 5, nb_barres, pas_reel)

# (b) Tests de la loi Exponentielle : loi reelle
#50 valeurs suivant une loi exponentielle (l=0.02)
loi_exp(50, 0.02, nb_barres, pas_reel)
#10000 valeurs suivant une loi exponentielle (l=0.02)
loi_exp(10000, 0.02, nb_barres, pas_reel)
#10000 valeurs suivant une loi exponentielle (l=0.8)
loi_exp(10000, 0.8, nb_barres, pas_reel)

#(c) Tests de la loi géométrique : loi discrète
#50 valeurs suivant une loi géométrique (p=0.07)
loi_geo(50, 0.07, nb_barres, pas_discret)
#10000 valeurs suivant une loi géométrique (p=0.07)
loi_geo(10000, 0.07, nb_barres, pas_discret)
#10000 valeurs suivant une loi géométrique (p=0.2)
loi_geo(10000, 0.2, nb_barres, pas_discret)

#(d)Tests de la loi de Poisson : loi discrète
#50 valeurs suivant une loi de Poisson (l=5)
loi_poisson(50, 5, nb_barres, pas_discret)
#10000 valeurs suivant une loi de Poisson (l=5)
loi_poisson(10000, 5, nb_barres, pas_discret)
#10000 valeurs suivant une loi de Poisson (l=0.5)
loi_poisson(10000, 0.5, nb_barres, pas_discret)
#10000 valeurs suivant une loi de poisson (l=50)
loi_poisson(10000, 50, nb_barres, pas_discret)

#(e) Tests de la loi Normale : loi continue
#50 valeurs suivant une loi normale(esperance=0 et ecar-type=1)
loi_normale(50, 0, 1, nb_barres, pas_reel)
#10000 valeurs suivant une loi normale ( esperance = 0 et ecart-type = 1)
loi_normale(10000, 0, 1, nb_barres, pas_reel)
#10000 valeurs suivant une loi normale (esperance=5, ecart-type=0.5)
loi_normale(10000, 5, 0.5, nb_barres, pas_reel)
#10000 valeurs suivant une loi normale (esperance=50, ecart-type=500)
loi_normale(10000, 50, 500, nb_barres, pas_reel)
