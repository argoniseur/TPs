#ifndef _ARBRE_H__
#define _ARBRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_GRDTree *GRDTree;

GRDTree creerArbreGRD();

bool isEmpty(GRDTree t);

void ajouterEntier(GRDTree t, int e);

void printTree(GRDTree t);

#endif