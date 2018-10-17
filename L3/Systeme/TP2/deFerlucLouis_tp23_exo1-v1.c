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
  //signal(sig, traiterSIGINT);
  printf(">> Ctrl-C/SIGINT recu par %d\n", getpid());
}


/*------------------------------------------------------------------------
 Code execute par chaque processus fils 
  ------------------------------------------------------------------------*/
void fils (/* A compléter */) {
	while(1)
		boucler();
  exit(0);
}

/*------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
	pid_t pidF;
	
	struct sigaction action;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = traiterSIGINT;
	
	if(sigaction(SIGINT, &action, NULL) != 0)
		erreur("SIGACTION", 1); 
  
  //signal(SIGINT, traiterSIGINT);
  printf("Processus (pere) de pid %d : protege contre SIGINT\n", getpid());
	pause();
  /* Créer son fils */
  switch (pidF = fork()) {
    case - 1 : erreur("Echec fork", 1);

    case 0 : fils();

    /* default : break; */		
  }
 
  printf("Processus (pere) de pid %d : j'ai cree un fils de pid %d\n",
	getpid(), pidF);

  /* Attendre éventuellement la fin de son fils */
  while(wait(NULL) != pidF);
	
  printf("Fin de l'application\n");
  return 0;
}
