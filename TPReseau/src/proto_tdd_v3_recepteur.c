/*************************************************************
* proto_tdd_v0 -  récepteur                                  *
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
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char* argv[])
{
    char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet, ack;        /* paquet utilisé par le protocole */
    int fin = 0, sequence = 0;            /* condition d'arrêt */
    uint8_t controle;
    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

	ack.type = ACK;
	ack.num_seq = 0;
	ack.lg_info = 0;
    /* tant que le récepteur reçoit des données */
    while ( ! fin ) {

        // attendre(); /* optionnel ici car de_reseau fct bloquante... */
        de_reseau(&paquet);
        controle = generer_controle(paquet);
        if (controle == paquet.somme_ctrl && sequence == paquet.num_seq) {
			printf("[TRP] reception %d\n", sequence);
			/* extraction des donnees du paquet recu */
			for (int i=0; i<paquet.lg_info; i++) {
				message[i] = paquet.info[i];
			}
			/* remise des données à la couche application */
			fin = vers_application(message, paquet.lg_info);
			ack.num_seq = paquet.num_seq;
			vers_reseau(&ack);
			sequence = inc(sequence, 8);
		}
		else if (controle == paquet.somme_ctrl && sequence != paquet.num_seq){
			vers_reseau(&ack);
		}
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;

}
