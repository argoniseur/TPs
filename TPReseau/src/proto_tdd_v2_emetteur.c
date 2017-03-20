/*************************************************************
* proto_tdd_v0 -  émetteur                                   *
* TRANSFERT DE DONNEES  v0                                   *
*                                                            *
* Protocole sans contrôle de flux, sans reprise sur erreurs  *
*                                                            *
* E. Lavinal - Univ. de Toulouse III - Paul Sabatier         *
**************************************************************/

#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char* argv[])
{
	char message[MAX_INFO]; /* message de l'application */
	int taille_msg, retransmission, sequence = 0;         /* taille du message */
	paquet_t paquet, ack;        /* paquet utilisé par le protocole */
	init_reseau(EMISSION);

	printf("[TRP] Initialisation reseau : OK.\n");
	printf("[TRP] Debut execution protocole transport.\n");

	/* lecture de donnees provenant de la couche application */
	de_application(message, &taille_msg);

	/* tant que l'émetteur a des données à envoyer */
	while ( taille_msg != 0 ) {

		/* construction paquet */
		for (int i=0; i<taille_msg; i++) {
			paquet.info[i] = message[i];
		}
		paquet.lg_info = taille_msg;
		paquet.type = DATA;
		paquet.num_seq = sequence % 2;
		sequence++;
		
		paquet.somme_ctrl = generer_controle(paquet);
		retransmission = 0;
		/* remise à la couche reseau */
		do {
			vers_reseau(&paquet);
			depart_temporisateur(100);
			retransmission++;
		} while (attendre() == TIMEOUT && retransmission != 20);
		arreter_temporisateur();
		if (retransmission < 20)
			de_reseau(&ack);
		/* lecture des donnees suivantes de la couche application */
		de_application(message, &taille_msg);
	}

	printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
	return 0;
}
