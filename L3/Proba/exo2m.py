# -*- coding: utf-8 -*-

import pickle

import matplotlib.pyplot as plt

# EXAM PROBAS 2017-2018
# EXERCICE 2 : Lois de probabilités


# Lecture du fichier au format Pickle
lois = pickle.load(open('exam_tp2017_matin.pkl', 'rb'))
loi1 = lois['loi1']
loi2 = lois['loi2']
loi3 = lois['loi3']
loi4 = lois['loi4']
loi5 = lois['loi5']
loi6 = lois['loi6']
loi7 = lois['loi7']
loi8 = lois['loi8']
loi9 = lois['loi9']
loi10 = lois['loi10']


plt.figure()
plt.hist(loi1, 20, normed=True, label='resultat pratique')
plt.title('loi1')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()

plt.figure()
plt.hist(loi2, 20, normed=True, label='resultat pratique')
plt.title('loi2')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()

plt.figure()
plt.hist(loi3, 20, normed=True, label='resultat pratique')
plt.title('loi3')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()

plt.figure()
plt.hist(loi4, 20, normed=True, label='resultat pratique')
plt.title('loi4')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()

plt.figure()
plt.hist(loi5, 20, normed=True, label='resultat pratique')
plt.title('loi5')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()

plt.figure()
plt.hist(loi6, 20, normed=True, label='resultat pratique')
plt.title('loi6')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()

plt.figure()
plt.hist(loi7, 20, normed=True, label='resultat pratique')
plt.title('loi7')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()

plt.figure()
plt.hist(loi8, 20, normed=True, label='resultat pratique')
plt.title('loi8')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()

plt.figure()
plt.hist(loi9, 20, normed=True, label='resultat pratique')
plt.title('loi9')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()

plt.figure()
plt.hist(loi10, 20, normed=True, label='resultat pratique')
plt.title('loi10')
plt.xlabel('Intervalles')
plt.ylabel('Probabilites')
plt.legend()
plt.show()