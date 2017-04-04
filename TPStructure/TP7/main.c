#include <stdio.h>
#include <stdlib.h>
#include "arbreGRD.h"


int main (int argc, char ** argv){
	GRDTree t;
	t = NULL;
	ajouterEntier(t, 1);
	ajouterEntier(t, 2);
	ajouterEntier(t, 3);
	ajouterEntier(t, 4);
	ajouterEntier(t, 5);
	ajouterEntier(t, 6);
	ajouterEntier(t, 7);
	ajouterEntier(t, 8);
	ajouterEntier(t, 9);

	printTree(t);
	return 0;
}
