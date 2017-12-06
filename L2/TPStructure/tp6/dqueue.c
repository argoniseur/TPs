#include "dqueue.h"

Deque initialiser_liste()
{
    Deque list=(Deque)malloc(sizeof(struct s_deque));
    list->sentinel=(Cellule)malloc(sizeof(struct s_cellule));
    list->sentinel->next=(Cellule)malloc(sizeof(struct s_cellule));
    list->sentinel->previous=(Cellule)malloc(sizeof(struct s_cellule));
    list->sentinel->previous=list->sentinel->next=list->sentinel;
    list->size=0;
    return list;
}

bool vide_liste(Deque list)
{
    return(!(list->size));
    
}

bool est_premier(Deque list,Cellule e)
{
    return(list->sentinel->next==e);
}

bool est_dernier(Deque list,Cellule e)
{
    return(list->sentinel->previous==e);
}

Element recherche_element(Deque list,char* chaine)
{
    Cellule search=(Cellule)malloc(sizeof(struct s_cellule));
    search=list->sentinel->next;
    while(search != list->sentinel)
    {
        if(!strcmp(chaine,search->elem->nom))
        {
                return(search->elem);
        }
        search=search->next;
        
    }
    return NULL;
}

Deque ajoute_element(Deque list,Cellule e)
{
    Cellule search=(Cellule)malloc(sizeof(struct s_cellule));
    search=list->sentinel->next;
    while(search != list->sentinel && e->elem->valeur>=search->elem->valeur)
    {
        search=search->next;
    }
    search->previous->next=e;
    e->previous=search->previous;
    search->previous=e;
    e->next=search;
    list->size++;
    return list;
}

Deque supprime_element(Deque list,Cellule e) // Oublie de gérer cas où élément est pas dans la liste
{
    Cellule search=(Cellule)malloc(sizeof(struct s_cellule));
    search=list->sentinel->next;
    while(search != list->sentinel && search!=e)
    {
        search=search->next;
    }
    search->previous->next=search->next;
    search->next->previous=search->previous;
    free(search);
    list->size--;
    return list;
}

void imprimer_liste_croissant(Deque list,bool sens)
{
    Cellule iterateur=(Cellule)malloc(sizeof(struct s_cellule));
    if(sens)
    {
        iterateur=list->sentinel->next;
        while(iterateur != list->sentinel)
        {
            printf("|%d , %s   ",iterateur->elem->valeur,iterateur->elem->nom);
            iterateur=iterateur->next;
        }
    }
    else
    {
        iterateur=list->sentinel->previous;
        while(iterateur != list->sentinel)
        {
            printf("|%d , %s   ",iterateur->elem->valeur,iterateur->elem->nom);
            iterateur=iterateur->previous;
        }
    }
    printf("\n");
}

/* Vide le buffer de fgets */
void viderBuffer(){
	int c = 0;
	while (c != '\n' && c != EOF)
		c = getchar();
}

Element saisir(){
	Element e = (Element)malloc(sizeof(struct s_element));
	char* tmp;
	char* c = (char*)malloc(100*sizeof(char));
	int x;
	
	printf("Nom: ");
	fgets(c,100,stdin);
	tmp = strchr(c, '\n');
	*tmp = '\0';
	
	printf("Note: ");
	scanf("%d", &x);
	
	e->valeur = x;
	e->nom = c;
	viderBuffer();
	return e;
}
