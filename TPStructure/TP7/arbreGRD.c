#include <stdio.h>
#include <stdlib.h>
#include "arbreGRD.h"

struct s_GRDTree {
	int key;
	struct s_GRDTree *left;
	struct s_GRDTree *right;
};

GRDTree creerArbreGRD(){
	return NULL;
}

bool isEmpty(GRDTree t){
	return (t == NULL);
}

void ajouterEntier(GRDTree t, int e){
    GRDTree tmpTree = t;

    GRDTree elem = (GRDTree)malloc(sizeof(struct s_GRDTree));
    elem->key = e;
    elem->left = NULL;
    elem->right = NULL;

    if(tmpTree){
    	do{
        	if(e > tmpTree->key){
        		if(!tmpTree->right)
            		tmpTree->right = elem;
            	tmpTree = tmpTree->right;
        	}
        	else{
        		if(!tmpTree->left)
					tmpTree->left = elem;
            	tmpTree = tmpTree->left;
        	}
    	}while(tmpTree);
    }
	else
		t = elem;
}

void printTree(GRDTree tree){
	if(!tree)
		return;
    if(tree->left)
    	printTree(tree->left);
    printf("Cle = %d\n", tree->key);
    if(tree->right)
    	printTree(tree->right);
}