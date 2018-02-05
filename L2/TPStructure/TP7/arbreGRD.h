#ifndef _ARBRE_H__
#define _ARBRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

typedef struct s_GRDTree *GRDTree;

GRDTree creerArbre();

GRDTree construireArbre(GRDTree left,GRDTree right, int key);

GRDTree ajouterEntier(GRDTree *t, int v);

bool estVide(GRDTree t);

void triGRD(GRDTree t);

void deleteTree(GRDTree t);

/* ***** Partie 2 ******** */

int saisir(Queue *q);

void vider_Tampon(GRDTree *t, Queue *q, int symbole);

int min(GRDTree t);

void extract_min(GRDTree *t, int val);

int vider_Arbre(GRDTree *t, Queue *q);

#endif
