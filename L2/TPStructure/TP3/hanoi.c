/*Version itérative tour hanoi*/

#include <stdio.h>
#include <stdbool.h>

/* includes "application" */
#include "elt_pile.h"
#include "pile.h"

void saisir_pile(T_pile* p)
{
    int i;
    int nb;
    printf("Saisir le nombre d'anneau nb≥1 pas trop grand:");
    scanf("%d",&nb);
    for (i=0; i<nb; i=i+1)
    {
        T_element element;
        saisir_element(&element);
        empiler(p,element);
    }
}

void swap(int a, int b, int c){
    int temp1, temp2;
    temp1=a;
    temp2=b;
    a=c;
    b=temp1;
    c=temp2;
}

int main(){
    int d, inter, a;
    T_pile col[3];/* 1 tableau de 3 piles*/
    /*Initialisation des trois piles du tableau comme vide*/
    initialiser_pile(&col[0]);
    initialiser_pile(&col[1]);
    initialiser_pile(&col[2]);
    /*Choix du nombre de disque sur la pile 1 => 1 tour de hanoi*/
    saisir_pile(&col[0]);
    /*cas impaire*/
    if(sommet_pile(col[0]) % 2 != 0){
        while(!pile_vide(col[0]) || !pile_vide(col[1])){
            d=0; inter=1; a=2;
            int cpt; /*le compteur est incrementé à chaque passage col[0]--->col[2]*/
            empiler(&col[a],sommet_pile(col[d]));
            depiler(&col[d]);/*D-->A*/
            printf("%d------>%d\n",d,a);
            cpt++;
            /* cycle de passage divisé en bloc de trois deplacement */
            while(cpt != 3){
                if(cpt==1){
                    empiler(&col[inter],sommet_pile(col[d]));
                    depiler(&col[d]);/*D--->I*/
                    printf("%d------>%d\n",d,inter);
                    empiler(&col[inter],sommet_pile(col[a]));
                    depiler(&col[a]);/*A-->I*/
                    printf("%d------>%d\n",a,inter);
                }
                else{
                    empiler(&col[d],sommet_pile(col[inter]));
                    depiler(&col[inter]);/*I-->D*/
                    printf("%d------>%d\n",inter,d);
                    empiler(&col[a],sommet_pile(col[inter]));
                    depiler(&col[inter]);/*I-->A*/
                    printf("%d------>%d\n",inter,a);
                }
                empiler(&col[a],sommet_pile(col[d]));
                depiler(&col[d]);/*D-->A*/
                printf("%d------>%d\n",d,a);/*deplacement precedant l'inversion en mirroir des 2 déplacement suivant par rapport au deux precedant*/
                cpt++;
            }
            swap(d,inter,a);/*echange suivant ordre trigonométrique*/
        }
    }
    /*cas pair*/
        if(sommet_pile(col[0]) % 2 == 0){
        while(!pile_vide(col[0]) || !pile_vide(col[1])){
            d=0; inter=1; a=2;
            int cpt; /*le compteur est incrementé à chaque passage col[0]--->col[2]*/
            empiler(&col[inter],sommet_pile(col[d]));
            depiler(&col[d]);/*D-->A*/
            printf("%d------>%d\n",d,inter);
            cpt++;
             /* cycle de passage divisé en bloc de trois deplacement */
            while(cpt != 3){
                if(cpt==1){
                    empiler(&col[a],sommet_pile(col[d]));
                    depiler(&col[d]);/*D--->I*/
                    printf("%d------>%d\n",d,a);
                    empiler(&col[inter],sommet_pile(col[a]));
                    depiler(&col[a]);/*A-->I*/
                    printf("%d------>%d\n",a,inter);
                }
                else{
                    empiler(&col[d],sommet_pile(col[a]));
                    depiler(&col[a]);/*I-->D*/
                    printf("%d------>%d\n",a,d);
                    empiler(&col[a],sommet_pile(col[inter]));
                    depiler(&col[inter]);/*I-->A*/
                    printf("%d------>%d\n",inter,a);
                }
                empiler(&col[inter],sommet_pile(col[d]));
                depiler(&col[d]);/*D-->A*/
                printf("%d------>%d\n",d,inter);/*deplacement precedant l'inversion en mirroir des 2 déplacement suivant par rapport au deux precedant*/
                cpt++;
            }
            swap(d,inter,a);/*echange suivant ordre trigonométrique*/
        }
    }
    return 0;
}
                
                
       
    
    
    
