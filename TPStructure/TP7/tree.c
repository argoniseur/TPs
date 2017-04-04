#include "tree.h"
#include "queue.h"

tree *creerArbreGRD() { return NULL; }

bool empty(tree *t) { return t == NULL; }

tree *ajouterEntier(tree *t, int e) {

  if (empty(t)) {
    t = (tree *)malloc(sizeof(tree));
    t->left = NULL;
    t->right = NULL;
    t->root = e;
    t->nb_branche = 1;
  } else {
    if (e <= t->root) {
      t->left = ajouterEntier(t->left, e);
    } else if (e > t->root) {
      t->right = ajouterEntier(t->right, e);
    }
  }
  t->nb_branche++;
  return t;
}

void print(tree *t) {
  if (!empty(t)) {
    print(t->left); // appel récursif vers le sous arbre gauche
    printf("%d ", t->root);
    print(t->right); // appel récursif vers le sous arbre droit
  }
}

///////////////////////////////////TP8//////////////////////////////////

// Phase 1
int saisir(Queue *q) {
  int symbole = 0;
  // ENTREZ -1 POUR QUITTER LA SAISIE
  init_Queue(q);
  for (int i=0;i<5;i++)
  	q->tab[i]=0;
  symbole = -2;

  while (symbole != -1 && !full_Queue(*q)) {
  printf("entrez des nombres, tapez -1 pour arreter \n");
    scanf("%d", &symbole);
    if (symbole != -1) {
      push(q, symbole);
    }
  }
  return (symbole == -1);
}

// Phase 2
void vider_Tampon(tree **t, Queue *q, int symbole) {
  while (!empty_Queue(*q)) {
    *t = ajouterEntier(*t, q->tab[q->head]);
    pop(q);
  }

  while (!symbole) {
    symbole = saisir(q);
    while (!empty_Queue(*q)) {
      *t = ajouterEntier(*t, q->tab[q->head]);
      pop(q);
    }
  }
}

int min(tree *t) {
  while (t->left != NULL)
    t = t->left;
  return t->root;
}

void extract_min(tree **t, int val) {
  tree *tmp;
  if ((*t)->root == val) {
    if ((*t)->left != NULL) {
      tmp = (*t)->left;
      while (tmp->right != NULL) {
        tmp = tmp->right;
      }
      tree *aux = *t;
      tmp->right = (*t)->right;
      *t = (*t)->left;
      free(aux);
    } else {
      tree *aux = *t;
      *t = (*t)->right;
      free(aux);
    }
  } else {
    if (val < (*t)->root) {
      extract_min(&(*t)->left, val);
    } else {
      extract_min(&(*t)->right, val);
    }
  }
}

int vider_Arbre(tree **t, Queue *q) {

  // int mini = min(*t);
  // extract_min(t, mini);
  // push(q, mini);
  // printf("min=%d\n", mini);
	init_Queue(q);
	for (int i=0;i<5;i++)
		q->tab[i]=0;
  while (!empty(*t) && !full_Queue(*q)) {
    int mini = min(*t);
    extract_min(t, mini);
    push(q, mini);
  }
  return (!empty(*t));
}

void vider_queue(FILE *f_in, Queue *q) {

  while (!empty_Queue(*q)) {
    fprintf(f_in, "%d ", q->tab[q->head]);
    pop(q);
  }
}
