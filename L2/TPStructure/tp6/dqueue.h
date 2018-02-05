#ifndef __DEQUE_H__
#define __DEQUE_H__
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct s_element 
{
    unsigned int valeur;
    char * nom;
}*Element;

typedef struct s_cellule
{
        Element elem;
        struct s_cellule *next;
        struct s_cellule *previous;
}*Cellule;

typedef struct s_deque
{
    Cellule sentinel;
    int size;
}*Deque;

Deque initialiser_liste();

bool vide_liste(Deque list);

bool est_premier(Deque list,Cellule e);

bool est_dernier(Deque list,Cellule e);

Element recherche_element(Deque list,char* chaine);

Deque ajoute_element(Deque list,Cellule e);

Deque supprime_element(Deque list,Cellule e);

void imprimer_liste_croissant(Deque list,bool sens);

void viderBuffer();

Element saisir();

/* ************************ ITERATEUR ************************* */

typedef struct s_dqueue_iterator{
    Deque l;
    Cellule current;
    Cellule (*next) (Cellule);
    Cellule begin;
}*DqueueIterator;

DqueueIterator deque_iterator_create(Deque l);

bool hasNext (DqueueIterator i);

bool hasPrevious (DqueueIterator i);

Cellule next(DqueueIterator i);

Cellule previous(DqueueIterator i);

DqueueIterator begin(DqueueIterator i);

DqueueIterator end(DqueueIterator i);

void map(Deque l, void(*process)(unsigned int *, void*), void *user_data);

#endif

