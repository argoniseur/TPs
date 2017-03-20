#ifndef __COUCHE_TRANSPORT_H__
#define __COUCHE_TRANSPORT_H__

#include <stdint.h> /* uint8 */
#define MAX_INFO 96

/*************************
 * Structure d'un paquet *
 *************************/

typedef struct paquet_s {
    uint8_t type;         /* type de paquet, cf. ci-dessous */
    uint8_t num_seq;      /* numéro de séquence */
    uint8_t lg_info;      /* longueur du champ info */
    uint8_t somme_ctrl;   /* somme de contrôle */
    char info[MAX_INFO];  /* données utiles du paquet */
} paquet_t;

/******************
 * Types de paquet *
 ******************/
#define CON_REQ       0  /* demande d'établissement de connexion */
#define CON_ACCEPT    1  /* acceptation de connexion */
#define CON_REFUSE    2  /* refus d'établissement de connexion */
#define CON_CLOSE     3  /* notification de déconnexion */
#define CON_CLOSE_ACK 4  /* accusé de réception de la déconnexion */
#define DATA          5  /* données de l'application */
#define ACK           6  /* accusé de réception des données */
#define NACK          7  /* accusé de réception négatif */
#define OTHER         8  /* extensions */



/* ********************************** */
/* Fonctions pour protocole Go-Back-N */
/* ********************************** */

uint8_t generer_controle(paquet_t paquet);

int inc(int curseur, int taille);

/*--------------------------------------*
 * Fonction d'inclusion dans la fenetre *
 *--------------------------------------*/
int dans_fenetre(unsigned int inf, unsigned int pointeur, int taille);


#endif
