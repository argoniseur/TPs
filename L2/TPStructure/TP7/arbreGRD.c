#include <stdio.h>
#include <stdlib.h>
#include "arbreGRD.h"

struct s_GRDTree {
	int key;
	struct s_GRDTree *left;
	struct s_GRDTree *right;
	struct s_GRDTree *parent;
};

GRDTree creerArbre(){
	return NULL;
}

GRDTree construireArbre(GRDTree left,GRDTree right, int key){
	GRDTree t=(GRDTree)malloc(sizeof(struct s_GRDTree));
	t->parent = NULL;
	t->left = left;
	t->right = right;
	t->key = key;

	if(left)
		left->parent = t;

	if(right)
		right->parent = t;
  
	return t;
}


GRDTree ajouterEntier(GRDTree *t, int v){
	if(*t==NULL)
		return (*t=construireArbre(NULL,NULL,v));
  
	if(v<(*t)->key){
		(*t)->left=ajouterEntier(&((*t)->left),v);
		(*t)->left->parent=*t;
	}
  
	else if(v>(*t)->key){
		(*t)->right=ajouterEntier(&((*t)->right),v);
		(*t)->right->parent=*t;
	}
	return *t;
}


bool estVide(GRDTree t){
	if(t==NULL)
		return true;
    
	return false; 
}

void triGRD(GRDTree t){
	if(t==NULL)
		return;
    
	triGRD(t->left);
	printf("%d ",t->key);   
	triGRD(t->right);
    
}


void deleteTree(GRDTree t){
    if(t == NULL)
        return;
    
    deleteTree(t->left);
    deleteTree(t->right);
    
    free(t);
}

/* ******************* Fonctions de la partie 2 ************************* */

int saisir(Queue *q){
    int symbole = 0;
    init_Queue(q);
    for (int i=0;i<5;i++)
    	q->tab[i]=0;
    symbole = -2;

    while (symbole != -1 && !full_Queue(*q)){
		scanf("%d", &symbole);
		if (symbole != -1){
			push(q, symbole);
		}
    }
    return (symbole == -1);
}

void vider_Tampon(GRDTree *t, Queue *q, int symbole){
    while (!empty_Queue(*q)){
        *t = ajouterEntier(t, q->tab[q->head]);
        pop(q);
    }

    while (!symbole){
        symbole = saisir(q);
        while (!empty_Queue(*q)){
            *t = ajouterEntier(t, q->tab[q->head]);
            pop(q);
        }
    }
}

int min(GRDTree t){
    while (t->left != NULL)
        t = t->left;
    return t->key;
}

void extract_min(GRDTree *t, int val){
    GRDTree tmp;
    if ((*t)->key == val){
        if ((*t)->left != NULL){
            tmp = (*t)->left;
            while (tmp->right != NULL){
                tmp = tmp->right;
            }
            GRDTree aux = *t;
            tmp->right = (*t)->right;
            *t = (*t)->left;
            free(aux);
        }
        else{
            GRDTree aux = *t;
            *t = (*t)->right;
            free(aux);
        }
    }
    else{
        if (val < (*t)->key){
            extract_min(&(*t)->left, val);
        }
        else{
            extract_min(&(*t)->right, val);
        }
    }
}

int vider_Arbre(GRDTree *t, Queue *q){
	init_Queue(q);
	for (int i=0;i<5;i++)
		q->tab[i]=0;
    while (*t != NULL && !full_Queue(*q)){
        int mini = min(*t);
        extract_min(t, mini);
        push(q, mini);
    }
    return (*t != NULL);
}
