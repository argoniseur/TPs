#ifndef PILESTATIQUE
#define PILESTATIQUE

#include "elt_pile.h"
#include <stdbool.h>

#define TAILLEMAX 8

/* ----------------------------------
        Déclaration des types
   --------------------------------*/

/* Déclaration du type d'une pile (avec masquage)*/

typedef struct cell* T_pile;



/* ----------------------------------
            Constructeurs
   --------------------------------*/

/*
 * Données:
 * Objet: Initialisation d'une T_pile
 * Résultats: la T_pile p créée
*/
void initialiser_pile(T_pile *p);

/*
 * Données: un T_element el, une T_pile p
 * Objet: empiler el sur la pile p
 * Résultats: la T_pile p modifiée
*/
void empiler(T_pile *p, T_element el);

/*
 * Données: une T_pile p
 * Objet: Suppression du T_element situé au sommet de la T_pile p
 * Résultats: la T_pile p modifiée
*/
void depiler(T_pile *p);


/* ----------------------------------
            Accesseurs
   --------------------------------*/

/*
 * Données: une T_pile p
 * Objet: Accéder au T_element situé au sommet de la T_pile p
 * Résultats: le T_element renvoyé
*/
T_element sommet_pile(T_pile p);

/*
 * Données: une T_pile p
 * Objet: Afficher une T_pile à partir du sommet
 * Résultats:
*/
void afficher_pile(T_pile p);

/*
 * Données: une T_pile p
 * Objet: Déterminer si la T_pile p est vide
 * Résultats: un booléen renvoyé
*/
bool pile_vide(T_pile p);

/*
 * Données: une T_pile p
 * Objet: Déterminer si la T_pile p est pleine
 * Résultats: un booléen renvoyé
*/
bool pile_pleine(T_pile p);


#endif





