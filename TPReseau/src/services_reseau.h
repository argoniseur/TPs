/************************************************************
 *      Simulation d'une PILE  PHYSIQUE-RESEAU              *
 *                                                          *
 * (v 1.4)                                                  *
 * P. Torguet & E. Lavinal                                  *
 * Université de Toulouse III - Paul Sabatier               *
 ************************************************************/

#ifndef __RESEAU_H__
#define __RESEAU_H__

#include "couche_transport.h" /* paquet_t */

/* pour init_reseau() */
#define EMISSION  0
#define RECEPTION 1

/* pour attendre() */
#define PAQUET_RECU 0
#define TIMEOUT 1

/* ============================ */
/* Initialisation couche réseau */
/* ============================ */

/************************************************************
 * Initialisation de le couche réseau. Le paramètre rôle    *
 * doit être égal à 1 pour la réception, 0 pour l'émission. *
 ************************************************************/
void init_reseau(int role);

/************************************************************************
 * Initialisation de le couche réseau en mode "réparti".                *
 * (c'est-à-dire, emetteur et recepteur sur machines distinctes)        *
 * Paramètres :                                                         *
 *    rôle : doit être égal à 1 pour la réception, 0 pour l'émission.   *
 *    port_local : port "transport" local                               *
 *    hote_distant : @ IP du destinataire (l'emetteur ou le récepteur)  *
 *    port_distant : port "transport" du destinataire (idem E ou R)     *
 ************************************************************************/
void init_reseau_mode_reparti(int role, unsigned short port_local, char* hote_distant, unsigned short port_distant);


/* ============================================================= */
/* Primitives de service pour émission et réception sur le canal */
/* ============================================================= */

/*****************************************************
 * Remet un paquet à la couche réseau pour envoi     *
 * sur le support de communication.                  *
 *****************************************************/
void vers_reseau(paquet_t *paquet);

/***********************************************************
 * Prélève un paquet de la couche réseau (N.B. : fonction  *
 * bloquante tant qu'un paquet n'est pas reçu).            *
 ***********************************************************/
void de_reseau(paquet_t *paquet);

/* =============================================== */
/* Fonctions utilitaires pour la gestion de timers */
/* =============================================== */

/*******************************************************
 * Démarre le temporisateur qui s'arrête après         *
 * ms millisecondes (ms doit être un multiple de 100)  *
 *******************************************************/
void depart_temporisateur(int ms);

/****************************
 * Arrête le temporisateur  *
 ****************************/
void arreter_temporisateur();

/****************************************************************
 * Fonction qui attend un évènement (paquet reçu ou timeout).   *
 * (N.B. : fonction bloquante)                                  *
 * Renvoie :  0 si une paquet reçu est disponible,              *
 *            1 si un timeout a été généré                      *
 ****************************************************************/
int attendre();

#endif
