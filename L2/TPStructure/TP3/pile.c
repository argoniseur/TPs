#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  /*contient la constante EXIT_FAILURE*/
#include <assert.h>
#include "pile.h"

/* masquage de types */

typedef struct s_element{
    T_element value;
    struct s_element *next;
}*Element;

struct cell{
	Element tete;
 } ;


void initialiser_pile(T_pile *p){
   //allocation de la structure dans le tas
   *p=(T_pile) malloc(sizeof (struct cell));
   (*p)->tete = NULL;
}


void afficher_pile(T_pile p){
	Element new;
	new = p->tete;
	while(new != NULL){
		afficher_element(new->value);
		new = new->next;
	}
}


bool pile_vide(T_pile p){
    return (p->tete == NULL);
}


bool pile_pleine(T_pile p){
    return 0;
}


void empiler(T_pile *p, T_element el){
	Element new = (Element)malloc(sizeof(struct s_element));
	new->value = el;
	new->next = (*p)->tete;
	(*p)->tete = new;
}




void depiler(T_pile *p){
	if (pile_vide(*p)){
        fprintf(stderr,"\ndepiler: pile vide !\n");
        exit(EXIT_FAILURE);
    }
	else
		assert(!pile_vide(*p));
		Element e = (*p)->tete;
		(*p)->tete = e->next;
		free(e);
}



T_element sommet_pile(T_pile p)
{
	if (pile_vide(p)){
        fprintf(stderr,"\nsommet_pile: pile vide !\n");
        exit(EXIT_FAILURE);
    }
	else{
        return p->tete->value;
    }
}













