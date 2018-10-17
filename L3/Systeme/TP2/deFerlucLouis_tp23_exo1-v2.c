/**-------------------------------------------------------------------------
  TP2 - Squelette code exercice 1-V1
  Compilation : gcc tp23_exo1-v1_base.c boucler.o -o tp23_exo1-v1 -Wall
--------------------------------------------------------------------------**/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "boucler.h"

/*------------------------------------------------------------------------
 Fonction d'affichage d'une erreur selon la cause de l'echec d'une primitive
 Arret du processus avec retour valant codeRetour
  ------------------------------------------------------------------------*/
void erreur (char *msg, int codeRetour) {
  perror(msg);
  exit(codeRetour);
}

/*------------------------------------------------------------------------
 Traitement associé à SIGINT
  ------------------------------------------------------------------------*/
void traiterSIGINT (int sig) {
  printf(">> Ctrl-C/SIGINT recu par %d\n", getpid());
  printf("Processus de pid %d: je vais executer \"praugkiboukl\"\n", getpid());
  
}


/*------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
  
  signal(SIGINT, traiterSIGINT);
  printf("Processus (pere) de pid %d : protege contre SIGINT\n", getpid());
  pause();

  execlp("/home/dfl1826a/Documents/git/TPs/L3/Systeme/TP2/praugkiboukl", "praugkiboukl", NULL);

  printf("Fin de l'application\n");
  return 0;
}
