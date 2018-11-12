/**-------------------------------------------------------------------------
  TP3 - Squelette code exercice 3
  Compilation : gcc tp23_exo3_base.c -o tp23_exo3 -Wall
--------------------------------------------------------------------------**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define LG_MAX 80

int dureePeriode;

int num = 0;

/*-----------------------------
 * Envoyer un message a chaque fois que le delai est ecoule
 * ----------------------------*/
void envoyerMessage (int sigRecu) {
  signal(envoyerMessage,SIGALRM);
  /* Constituer le message */
  sprintf(monMsg, "%s %d %s %s", "Message numero", num, " envoye a ", (time(&t), ctime(&t)));
  num++;

  /* L'envoyer */

  /* Armer la periode suivante */
  alarm(dureePeriode);
}

/*-----------------------------*/
void fils (void) {
 char leMsg[LG_MAX];

 /* Orienter le tube */
 close(tube[1]);

 /* Boucler pour lire les messages en les affichant */
 // printf("\tFils - Message de mon pere : %s\n", leMsg);


 exit(0);
}

/*-----------------------------*/
int main (int argc, char *argv[]) {

  int i;
  char c;
  int tube;
  /* Verifier les parametres */
  if (argc != 2) {
    printf("Usage : %s <Periode en secondes> \n", argv[0]);
    exit(1);
  }

  /* Recuperer la duree de la periode */
  dureePeriode = atoi(argv[1]);

  /* Creer le tube de communication */
  if (pipe(tube) != 0)
    perror("pipe");

  /* Creer le fils qui herite du tube */
  switch(fork()) {
    case -1  : perror("Echec fork ");
               exit(3);
    case 0   : fils();
    default  : break;
  }

  /* Orienter le tube */
  close(tube[0]);

  /* Se proteger contre le signal SIGALRM */
  

  /* Armer le traitement periodique */
  

  /* Boucler sans rien faire */
  while (num < 10);
  close(tube[1]);
  return 0;
}

