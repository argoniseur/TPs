#include <stdio.h>
#include "elt_pile.h" /* contient la  Def du type T_element a empiler */




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

