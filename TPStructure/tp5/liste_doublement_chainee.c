#include "liste_doublement_chainee.h"


struct s_element{
	unsigned int valeur;
	char* chaine;
};

typedef struct s_node{
	struct s_node *suivant;
	Element elem;
	struct s_node *precedent;
}*Node;

struct s_listeDouble{
	Node liste;
};


ListeDouble initialiser_liste(){
	ListeDouble l = (ListeDouble)malloc(sizeof(struct s_listeDouble));
	l->liste->elem = NULL;
	l->liste->suivant = l->liste->precedent;
	l->liste->precedent = l->liste->suivant;
	return l;
}

bool vide_liste(ListeDouble l){
	return !(l->liste->suivant == NULL);
}

bool est_premier(ListeDouble l, Element e){
	return (l->liste->suivant->elem == e);
}

bool est_dernier(ListeDouble l, Element e){
	return (l->liste->precedent->elem == e);
}

Element recherche_element(ListeDouble l, char* c){
    Node iterateur = (Node)malloc(sizeof(struct s_node));
    iterateur = l->liste->suivant;
    while(iterateur != l->liste){
        if(!strcmp(c,iterateur->elem->chaine))
            return iterateur->elem;
        iterateur = iterateur->suivant;
    }
    return l->liste->elem;
}

/*
ListeDouble ajoute_element(ListeDouble l, Element e){
	Node iterateur = (Node)mallol->liste->precedentc(sizeof(struct s_node));
	iterateur = l->liste->suivant;
	while(iterateur->suivant != l->liste && iterateur->elem->valeur <= e->valeur){
		iterateur = iterateur->suivant;
	}
	
		
	return l;
}*/
