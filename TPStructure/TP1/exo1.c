#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define TAILLE_MAX 20

typedef struct s_ensemble{
	int t[TAILLE_MAX];
	int nb_elements;
}Ensemble;


void Vide(Ensemble *e){
	e->nb_elements = 0;
}

void Ajout(Ensemble *e, int x){
		assert(e->nb_elements < TAILLE_MAX);
		e->t[e->nb_elements] = x;
		e->nb_elements++;
}

bool Appartient(Ensemble e, int x){
	for(int i=0;i<e.nb_elements;i++){
		if(e.t[i] == x)
			return true;
	}
	return false;
}

bool Est_Vide(Ensemble e){
	return !(e.nb_elements);
}

void Union(Ensemble *e1, Ensemble e2){
	for(int i=0;i<e2.nb_elements;i++){
		if(!Appartient(*e1,e2.t[i]))
			Ajout(e1,e2.t[i]);
	}
}


int main(void){
	
	return 0;	
}
