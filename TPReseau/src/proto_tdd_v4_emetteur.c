/*************************************************************
* proto_tdd_v0 -  émetteur                                   *
* TRANSFERT DE DONNEES  v0                                   *
*                                                            *
* Protocole sans contrôle de flux, sans reprise sur erreurs  *
*                                                            *
* E. Lavinal - Univ. de Toulouse III - Paul Sabatier         *
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"
#define NUM_SEQ_MAX 8

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char* argv[])
{
	char message[MAX_INFO]; /* message de l'application */
	int taille_msg;         /* taille du message */
	int taille_fenetre = 4, borne_inf = 0, curseur = 0, evt, i, service = 0;
	paquet_t ack, tab_p[NUM_SEQ_MAX],connect;        /* paquet utilisé par le protocole */
	init_reseau(EMISSION);
	printf("[TRP] Initialisation reseau : OK.\n");
	printf("[TRP] Debut execution protocole transport.\n");

	/* lecture de donnees provenant de la couche application */
	de_application_mode_c(&service, message, &taille_msg);
	
	if (service == T_CONNECT){
		/* Si on recoit une demande de connexion */
		connect.type = CON_REQ;
		evt = 1;
		while(evt != 0){
			/* On envoie une demande de connexion au récepteur */
			vers_reseau(&connect);
			depart_temporisateur(100);
			evt = attendre();
		}
		arreter_temporisateur();
		attendre();
		de_reseau(&connect);
		
		switch(connect.type){
			case CON_ACCEPT:
				/* Si la réponse reçue est positive on notifie la couche application */
				vers_application_mode_c(T_CONNECT_ACCEPT, message, taille_msg);
				break;
			case CON_REFUSE:
				/* Si la réponse est négtive, on notifie application et on exit */
				vers_application_mode_c(T_CONNECT_REFUSE, message, taille_msg);
				exit(1);
				break;
		}
    }
	
	
	
	de_application_mode_c(&service, message, &taille_msg);
	/* tant que l'émetteur a des données à envoyer */
	while ((taille_msg != 0 || borne_inf != curseur) && service != T_DISCONNECT) {
		if(dans_fenetre(borne_inf, curseur, taille_fenetre) && taille_msg != 0){
			/* construction paquet */
			for (i=0; i<taille_msg; i++) {
				tab_p[curseur].info[i] = message[i];
			}
			tab_p[curseur].lg_info = taille_msg;
			tab_p[curseur].type = DATA;
			tab_p[curseur].num_seq = (uint8_t)curseur;
			
			tab_p[curseur].somme_ctrl = generer_controle(tab_p[curseur]);
			/* remise à la couche reseau */
			vers_reseau(&tab_p[curseur]);
			if(borne_inf == curseur){
				depart_temporisateur(100);
			}
			curseur = inc(curseur,NUM_SEQ_MAX);
			de_application_mode_c(&service, message, &taille_msg);
		}
		else{
			
			evt = attendre();
			if(!evt){
				de_reseau(&ack);
				if(dans_fenetre(borne_inf,ack.num_seq,taille_fenetre)){
					borne_inf = inc(ack.num_seq,NUM_SEQ_MAX);
					arreter_temporisateur();
					if(borne_inf != curseur)
						depart_temporisateur(100);
				}
			} // timeout
			else{
					i = borne_inf;
					printf("RETRANSMISSION\n");
					depart_temporisateur(100);
					while(i != curseur){
						vers_reseau(&tab_p[i]);
						i = inc(i, NUM_SEQ_MAX);
					}
			}
		}
		/* lecture des donnees suivantes de la couche application */
		
	}
	
	/* Fin de transmission, on demande la déconnexion */
	connect.type = CON_CLOSE;
	evt = 1;
	arreter_temporisateur();
	while(evt != 0){
		vers_reseau(&connect);
		depart_temporisateur(100);
		evt = attendre();
	}
	
	arreter_temporisateur();
	attendre();
	de_reseau(&connect);
	
	printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
	return 0;
}
