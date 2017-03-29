#ifndef _ENSEMBLEDQUEUE_H_
#define _ENSEMBLEDQUEUE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

/*définition opaque du type doublement chaînée*/
typedef struct s_dqueue *Dqueue;

/*définition du type Element*/
typedef struct s_element *Element;

typedef struct s_node *Node;


Dqueue initialiser_liste();

bool vide_liste(Dqueue q);

bool est_premier(Dqueue q, Element e);

bool est_dernier(Dqueue q, Element e);

Element create_elem(int v);

/* ************************************** ITERATOR ****************************** */

typedef struct s_dqueue_iterator *DqueueIterator;

bool hasNext (DqueueIterator i);

bool hasPrevious (DqueueIterator i);

Node next(DqueueIterator i);

Node previous(DqueueIterator i);

DqueueIterator begin(DqueueIterator i);

DqueueIterator end(DqueueIterator i);

#endif

