#include "liste_doublement_chainee.h"

typedef struct s_node{
	struct s_node *suivant;
	Element elem;
	struct s_node *precedent;
}*Node;

struct s_listeDouble{
	Node sentinel;
};


ListeDouble initialiser_liste(){
	ListeDouble l = (ListeDouble)malloc(sizeof(struct s_listeDouble));
	l->sentinel = (Node)malloc(sizeof(struct s_node));
	l->sentinel->suivant = (Node)malloc(sizeof(struct s_node));
	l->sentinel->precedent = (Node)malloc(sizeof(struct s_node));
	l->sentinel->suivant = l->sentinel;
	l->sentinel->precedent = l->sentinel;
	l->sentinel->elem = (Element)malloc(sizeof(struct s_element));
	l->sentinel->elem->valeur = 0;
	l->sentinel->elem->chaine = "";
	return l;
}

bool vide_liste(ListeDouble l){
	return !(l->sentinel->suivant == NULL);
}

bool est_premier(ListeDouble l, Element e){
	return (l->sentinel->suivant->elem == e);
}

bool est_dernier(ListeDouble l, Element e){
	return (l->sentinel->precedent->elem == e);
}

Element recherche_element(ListeDouble l, char* c){
    Node iterateur = (Node)malloc(sizeof(struct s_node));
    iterateur = l->sentinel->suivant;
    while(iterateur != l->sentinel){
        if(!strcmp(c,iterateur->elem->chaine))
            return iterateur->elem;
        iterateur = iterateur->suivant;
    }
    return l->sentinel->elem;
}


ListeDouble ajoute_element(ListeDouble l, Element e){
	Node it = (Node)malloc(sizeof(struct s_node));

	it = l->sentinel;
	
	while(it->suivant != l->sentinel && it->elem->valeur <= e->valeur){
		it = it->suivant;
	}
	it->elem = e;
	it->precedent = it;
	return l;
}

void imprimer_liste_croissant(ListeDouble l, bool sens){
	Node it = (Node)malloc(sizeof(struct s_node));
	it = l->sentinel;
	if(sens){
		while(it->suivant != l->sentinel){
			printf("1");
			it = it->suivant;
			printf("%s, %d\n", it->elem->chaine, it->elem->valeur);
		}
	}
}