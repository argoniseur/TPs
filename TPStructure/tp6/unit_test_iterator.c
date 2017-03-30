#include "dqueue.h"

int main(int argc, char ** argv){
	Deque list=initialiser_liste();
    Cellule e1=(Cellule)malloc(sizeof(struct s_cellule));
    e1->next=(Cellule)malloc(sizeof(struct s_cellule));
    e1->previous=(Cellule)malloc(sizeof(struct s_cellule));
    e1->elem=(Element)malloc(sizeof(struct s_element));
    e1->elem->valeur=1;
    e1->elem->nom="bonjour";
    ajoute_element(list,e1);


    Cellule e2=(Cellule)malloc(sizeof(struct s_cellule));
    e2->next=(Cellule)malloc(sizeof(struct s_cellule));
    e2->previous=(Cellule)malloc(sizeof(struct s_cellule));
    e2->elem=(Element)malloc(sizeof(struct s_element));
    e2->elem->valeur=2;
    e2->elem->nom="au revoir";
    ajoute_element(list,e2);
    
	DqueueIterator it=deque_iterator_create(list);
	Cellule e=(Cellule)malloc(sizeof(struct s_cellule));
	e->next=(Cellule)malloc(sizeof(struct s_cellule));
	e->previous=(Cellule)malloc(sizeof(struct s_cellule));
	e->elem=(Element)malloc(sizeof(struct s_element));
	
	begin(it);
	for(int i = 0;i < it->l->size;i++){
		printf("%d --- %s\n", it->current->elem->valeur, it->current->elem->nom);
		it->current = it->current->next;
	}
return 0;
}
