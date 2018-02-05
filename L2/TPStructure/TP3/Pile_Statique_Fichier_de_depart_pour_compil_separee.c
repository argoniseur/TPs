/*
31 01 2013
Pile statique : version monofichier pour découpage modulaire avec masquage
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define TAILLEMAX 50

typedef int T_element;
typedef T_element T_tab[TAILLEMAX];

struct cell
 { T_tab  tab;
   int    tete; /*indice du sommet de la pile dans tab*/
 };

typedef struct cell* T_pile;

/************************************************************************************/

void saisir_element (T_element* el)
{
printf("\nTaper la valeur d'un element:");scanf("%d",el);
}


void afficher_element (T_element el)
{
printf("%3d",el);
}


void affecter_element (T_element* el1, T_element el2)
{
*el1=el2;
}
/********************************************************************/



void initialiser_pile(T_pile *p)
{
    //allocation de la structure dans le tas
   *p=(T_pile) malloc(sizeof (struct cell));
    (*p)->tete=-1;
}



bool pile_vide(T_pile p)
{
    return (p->tete==-1);
}


bool pile_pleine(T_pile p)
{
    return (p->tete==TAILLEMAX-1);
}


void afficher_pile(T_pile p)
{
if (!pile_vide(p))
    {
    int i;
    for(i=0; i<=p->tete; i=i+1)
        afficher_element(p->tab[i]);
    }
}




void empiler(T_pile *p, T_element el)
{
if (pile_pleine(*p))
    {
        fprintf(stderr,"\nEmpiler : pile pleine !\n");
        exit(EXIT_FAILURE);
    }
else
    {
        (*p)->tete=((*p)->tete) + 1;
        affecter_element(&((*p)->tab[(*p)->tete]),el);
    }
}




void depiler(T_pile *p)
{
if (pile_vide(*p))
    {
        fprintf(stderr,"\ndepiler: pile vide !\n");
        exit(EXIT_FAILURE);
    }
else (*p)->tete=(*p)->tete-1;
}



T_element sommet_pile(T_pile p)
{
 if (pile_vide(p))
    {
        fprintf(stderr,"\nsommet_pile: pile vide !\n");
        exit(EXIT_FAILURE);
    }
else
    {
        return((p->tab)[p->tete]);
    }
}


/****************************************************************/
void saisir_pile(T_pile* p)
{
    int i;
    int nb;
    printf("Taper le nombre d'elements de la pile:");
    scanf("%d",&nb);
    for (i=0; i<nb; i=i+1)
    {
        T_element element;
        saisir_element(&element);
        empiler(p,element);
    }
}

/****************************************************************/
int main(void)

{
   T_pile p1;
   initialiser_pile(&p1);
   printf("\npv=%5dpp=%5d\t",pile_vide(p1),pile_pleine(p1));

   fprintf(stderr,"\nEssai d'ecriture sur stderr!\n");

   empiler(&p1,2);
   depiler(&p1);
   empiler(&p1,2);
   empiler(&p1,3);
   printf("\npile:");   afficher_pile(p1);
   printf("\nsommet:");  printf("%3d",sommet_pile(p1));
   depiler(&p1);
   depiler(&p1);
   printf("\n\n");

   printf("\t\tpv=%2d pp=%2d",pile_vide(p1),pile_pleine(p1));
    int i=0;
    while (!pile_pleine(p1))
    {
      empiler(&p1,2*i);
      printf("\npile:");    afficher_pile(p1);
      printf("\nsommet:"); printf("%3d",sommet_pile(p1));
      printf("\tpv=%2dpp=%2d\n",pile_vide(p1),pile_pleine(p1));
      i=i+1;
    }

   printf("\nEssai d'empilage sur une pile pleine:\n");
       empiler(&p1,54);
       empiler(&p1,54);


    printf("\nFin normale du programme.\n");

return(0);
}














