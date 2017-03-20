#ifndef ELEMENTPILE
#define ELEMENTPILE

/* ----------------------------------
        Déclaration des types
   --------------------------------*/

/* Déclaration du type des éléments d'une pile */

typedef int T_element;

/* ----------------------------------
            Constructeurs
   --------------------------------*/
/*
 * Données:
 * Objet: Saisir un T_element  
 * Résultats: un T_element saisi  
*/
void saisir_element(T_element *el);

/*
 * Données: la valeur du T_element à copier :de , le nom du T_element
 *      	où se fait la copie: vers  
 * Objet: Copie d'un T_element dans un autre T_element  
 * Résultats: le T_element vers modifié  
*/
void affecter_element(T_element *vers, T_element de);


/* ----------------------------------
            Accesseurs
   --------------------------------*/

/*
 * Données: la valeur d'un T_element 
 * Objet: Afficher un T_element  
 * Résultats: 
*/
void afficher_element(T_element el);


#endif
