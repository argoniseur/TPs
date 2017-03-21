#ifndef _ENSEMBLE_H_
#define _ENSEMBLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*définition opaque du type doublement chaînée*/
typedef struct s_listeDouble *ListeDouble;

/*définition du type Element*/
typedef struct s_element *Element;

/**Constructeur: construit une liste vide
 * initialiser_liste: ->Dqueue
 */
ListeDouble initialiser_liste();

/**Constructeur: ajoute un element à la liste
 * ajoute_element: Dqueue X Element -> Dqueue
 */

ListeDouble ajoute_element(ListeDouble q, Element e);

/**OPERATEUR: verifie si la liste est vide
 * vide_liste:Dqueue -> BOOLEAN
 */

bool vide_liste(ListeDouble q);



/**OPERATEUR: verifie si l'element est le premier
 * est_premier: Dqueue X Element -> BOOLEAN
 *@pre (!vide_liste(q))
 */

bool est_premier(ListeDouble q, Element e);


/**OPERATEUR: verifie si l'element est le dernier
 * est_dernier: Dqueue X Element -> BOOLEAN
 *@pre (!vide_liste(q))
 */

bool est_dernier(ListeDouble q, Element e);


/**OPERATEUR: verifie l'appartenance de l'element à la liste
 * recherche_element: Dqueue X Element -> Element
 */

Element recherche_element(ListeDouble q, char* c);

/**OPERATEUR-DESTRUCTEUR: supprime un element
 * supprime_element:Dqueue X Element -> Dqueue
 *@pre (!vide_liste(q))
 */

ListeDouble supprime_element(ListeDouble q, Element e);

/**OPERATEUR:Affiche la liste dans l'ordre croissant ou décroissant selon la valeur du boolean. 
 * VRAI->croissant
 * FAUX ->decroissant
 */

void imprimer_liste_croissant(ListeDouble q, bool croissant);


#endif


