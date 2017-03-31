#include "liste_doublement_chainee.h"

int main(int argc,char* argv[])
{
    Deque list=initialiser_liste();
    Cellule e1=(Cellule)malloc(sizeof(struct s_cellule));
    e1->next=(Cellule)malloc(sizeof(struct s_cellule));
    e1->previous=(Cellule)malloc(sizeof(struct s_cellule));
    e1->elem=(Element)malloc(sizeof(struct s_element));
    e1->elem = saisir();
    ajoute_element(list,e1);


    Cellule e2=(Cellule)malloc(sizeof(struct s_cellule));
    e2->next=(Cellule)malloc(sizeof(struct s_cellule));
    e2->previous=(Cellule)malloc(sizeof(struct s_cellule));
    e2->elem=(Element)malloc(sizeof(struct s_element));
    e2->elem = saisir();
    ajoute_element(list,e2);

    if(est_premier(list,e1))
    {
        printf("e1 est premier\n");
    }
    if(est_dernier(list,e2))
    {
        printf("e2 est dernier\n");
    }

    printf("%d\n",recherche_element(list,"salut")->valeur);
    imprimer_liste_croissant(list,true);
    imprimer_liste_croissant(list,false);
    
	return 0;
}

