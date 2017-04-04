#ifndef _ARBRE_H__
#define _ARBRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"


typedef struct tree_s {
  int root;
  struct tree_s *left;
  struct tree_s *right;
  int nb_branche;
} tree;

tree * creerArbreGRD();
bool empty (tree *t);
tree * ajouterEntier(tree *t, int e);
void print(tree *t);


/////////////////////////////////////TP8/////////////////////////////
int saisir (Queue *q);
void vider_Tampon (tree **t, Queue *q, int symbole);
//int extract_min (tree *t);
void extract_min(tree **t, int val);
int vider_Arbre (tree **t, Queue *q);
int min(tree *t);
void vider_queue (FILE *f_in, Queue *q);

#endif
