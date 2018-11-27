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
int tube[2];
int num = 0;

/*-----------------------------
 * Envoyer un message a chaque fois que le delai est ecoule
 * ----------------------------*/

void envoyerMessage (int sigRecu) {
  signal(SIGALRM,envoyerMessage);
  char monMsg[LG_MAX];
  time_t t;
  /* Constituer le message */
  sprintf(monMsg, "%s %d %s %s", "Message numero", num, "envoye a", (time(&t), ctime(&t)));
  num++;
  /* L'envoyer */
  write(tube[1],monMsg,strlen(monMsg)+1);
  /* Armer la periode suivante */
alarm(dureePeriode);
}

/*-----------------------------*/
void fils (void) {
  char leMsg[LG_MAX];
 /* Orienter le tube */
 close(tube[1]); // le fils n'écrit pas sur le tube

 /* Boucler pour lire les messages en les affichant */
 while(read(tube[0],&leMsg,sizeof(leMsg))>0)
    printf("Fils - Message de mon pere: %s", leMsg);

  exit(0);
}

/*-----------------------------*/
int main (int argc, char *argv[]) {

  /* Verifier les parametres */
  if (argc != 2) {
    printf("Usage : %s <Periode en secondes> \n", argv[0]);
    exit(1);
  }

  /* Recuperer la duree de la periode */
  dureePeriode = atoi(argv[1]);

  /* Creer le tube de communication */
  if(pipe(tube)==-1){
      perror("erreur creation tube");
      exit(2);
  }

  /* Creer le fils qui herite du tube */
  switch(fork()) {
    case -1  : perror("Echec fork ");
               exit(3);
    case 0   : fils();
    default  : break;
  }

  /* Orienter le tube */
  close(tube[0]);
  //sleep(dureePeriode);
  /* Se proteger contre le signal SIGALRM */
  signal(SIGALRM,envoyerMessage); //à la reception du SIGALRM le programme ne s'arrete pas il execute la fct envoyerMessage
  /* Armer le traitement periodique */
  alarm(dureePeriode);

  /* Boucler sans rien faire */
  while (num < 10);
  return 0;
}