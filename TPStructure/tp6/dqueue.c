#include "dqueue.h"

//Définition du type element
struct s_element{
    int valeur;
};

struct s_node{
    Element elem;
    struct s_node *suivant;
    struct s_node *precedent;
};

struct s_dqueue{
    Node sentinel;
    int size;
};

Dqueue initialiser_liste(){
    Dqueue q = (Dqueue)malloc(sizeof(struct s_dqueue));
    q->sentinel->elem = NULL;
    q->sentinel->suivant = NULL;
    q->sentinel->precedent = NULL;
    q->size=0;
    return q;
}

bool vide_liste(Dqueue q){
    return (!(q->size));
}

bool est_premier(Dqueue q, Element e){
    return (q->sentinel->suivant->elem == e);
}

bool est_dernier(Dqueue q, Element e){
    return (q->sentinel->precedent->elem == e);
}

Element create_elem(int v){
    Element elem = (Element)malloc(sizeof(struct s_element));
    elem->valeur = v;
    return elem;
}

Dqueue ajoute_element(Dqueue l, Element e){
	Node it = (Node)malloc(sizeof(struct s_node));
	it = l->liste->suivant;
	while(it->suivant != l->liste && it->elem->valeur <= e->valeur){
		it = it->suivant;
	}
	
		
	return l;
}*/
