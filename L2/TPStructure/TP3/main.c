/*
29 01 2012
Pile statique avec typage masqué
*/

#include <stdio.h>
#include <stdbool.h>

/* includes "application" */
#include "elt_pile.h"
#include "pile.h"
#include <stdlib.h>

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

    /*saisir_pile(&p1);
    afficher_pile(p1);
    depiler(&p1);
    empiler(&p1,54);
    empiler(&p1,54);
    empiler(&p1,28);
    printf("\n%d ",sommet_pile(p1));afficher_pile(p1);
    printf("\nok");
    */


   fprintf(stderr,"\nEssai d'ecriture sur stderr!\n");

   empiler(&p1,2);
   depiler(&p1);
   empiler(&p1,2);
   empiler(&p1,3);
   printf("\npile:");   afficher_pile(p1);
   printf("\nsommet:");  printf("%3d",sommet_pile(p1));
   depiler(&p1);
   depiler(&p1);
   /* printf("\nsommet:"); afficher_element(sommet_pile(p1));*/
   printf("\n\n");

   printf("\t\tpv=%2d pp=%2d",pile_vide(p1),pile_pleine(p1));
    int i=0;
    while (i < 10)
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

    //libération de la mémoire pour la structure pointée par p1
    free(p1);
    printf("\nFin normale du programme.\n");

return(0);
}














