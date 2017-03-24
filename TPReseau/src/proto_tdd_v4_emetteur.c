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
		connect.type = CON_REQ;
		vers_reseau(&connect);
		while (connect.type != CON_ACCEPT){
			evt = attendre();
			if (!evt)
				de_reseau(&connect);
			if (connect.type == CON_REFUSE)
				exit (1);
	    }
    }
	
	de_application_mode_c(&service, message, &taille_msg);
	/* tant que l'émetteur a des données à envoyer */
	while (borne_inf != curseur && service != T_DISCONNECT) {
		if(dans_fenetre(borne_inf, curseur, taille_fenetre) && taille_msg != 0){
			/* construction paquet */
			for (i=0; i<taille_msg; i++) {
				tab_p[curseur].info[i] = message[i];
			}
			tab_p[curseur].lg_info = taille_msg;
			tab_p[curseur].type = DATA;
			tab_p[curseur].num_seq = (uint8_t)curseur;
			
			tab_p[curseur].somme_ctrl = generer_controle(tab_p[curseur]);
			printf("%hhu -- %hhu\n", curseur, tab_p[curseur].num_seq);
			/* remise à la couche reseau */
			vers_reseau(&tab_p[curseur]);
			if(borne_inf == curseur){
				depart_temporisateur(100);
			}
			curseur = inc(curseur,NUM_SEQ_MAX);
			// printf("%hhu -- %hhu\n", curseur, tab_p[curseur].num_seq);
			de_application_mode_c(&service, message, &taille_msg);
		}
		else{
			
			evt = attendre();
			if(!evt){
				de_reseau(&ack);
				printf("ack __ %d\n", ack.num_seq);
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
						printf("--> %d\n", i);
						vers_reseau(&tab_p[i]);
						i = inc(i, NUM_SEQ_MAX);
					}
			}
		}
		/* lecture des donnees suivantes de la couche application */
		
	}
	
	printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
	return 0;
}
