#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define TAILLE_MAX 20

typedef struct s_ensemble{
	int t[TAILLE_MAX];
	int nb_elements;
}Ensemble;


Ensemble Vide(Ensemble e){
	e.nb_elements = 0;
}

Ensemble Ajout(Ensemble e, int x){
		assert(e.nb_elements < TAILLE_MAX);
		e.t[e.nb_elements] = x;
		e.nb_elements++;
}

bool Appartient(Ensemble e, int x){
    int i;
	for(i=0;i<e.nb_elements;i++){
		if(e.t[i] == x)
			return true;
	}
	return false;
}

bool Est_Vide(Ensemble e){
	return !(e.nb_elements);
}

Ensemble Union(Ensemble e1, Ensemble e2){
    int i;
	for(i=0;i<e2.nb_elements;i++){
		if(!Appartient(e1,e2.t[i]))
			Ajout(e1,e2.t[i]);
	}
}

Ensemble Intersection(Ensemble e1, Ensemble e2){
    Ensemble e;
    int i, max;
    max = e1.nb_elements;
    if(e2.nb_elements > max)
        max = e2.nb_elements;
    for(i=0;i<max;i++){

    }
    return
}



int main(void){

	return 0;
}
