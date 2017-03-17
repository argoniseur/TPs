#include <stdio.h>
#include "couche_transport.h"
#include "services_reseau.h"

/* Ajouter ici vos fonctions utilitaires
 * (generer_controle, verifier_controle, connexion,...)
 */

uint8_t generer_controle(paquet_t paquet) {
	uint8_t somme = paquet.type ^ paquet.num_seq;
    somme = somme ^ paquet.lg_info;
    for (int i=0; i<paquet.lg_info; i++) {
		somme = somme ^ paquet.info[i];
	}
	return somme;
}

int inc(int curseur, int taille){
	curseur++;
	curseur = curseur % taille;
	return curseur;
}

/* ======================================================================= */
/* =================== Fenêtre d'anticipation ============================ */
/* ======================================================================= */

#define NUMEROTATION 8

/*--------------------------------------*/
/* Fonction d'inclusion dans la fenetre */
/*--------------------------------------*/
int dans_fenetre(unsigned int inf, unsigned int pointeur, int taille) {

    unsigned int sup = (inf+taille-1) % NUMEROTATION;

    return
    /* inf <= pointeur <= sup */
    ( inf <= sup && pointeur >= inf && pointeur <= sup ) ||
    /* sup < inf <= pointeur */
    ( sup < inf && pointeur >= inf) ||
    /* pointeur <= sup < inf */
    ( sup < inf && pointeur <= sup);
}


