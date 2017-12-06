#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 15 10:40:51 2017

@author: dfl1826a
"""

import numpy as np
import numpy.random as loi
import scipy.stats as loiT
import matplotlib.pyplot as plt


# TP PROBAS et STATISTIQUES en PYTHON 2
# EXERCICE 1 : comparaison de lois uniformes : theorique & pratique


# Loi uniforme
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

# (a) Tests de la loi Uniforme : loi discrete ou reelle au choix...
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

