/**-------------------------------------------------------------------------
  TP1 - Squelette code exercice 1-V2
  Compilation : gcc nomFic.c -o nomFic -lpthread
--------------------------------------------------------------------------**/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NB_THREADS_MAX  10
#define NB_FOIS         10
int nbAffichages;
/*------------------------------------------------------------------------
 * Affichage de l'identite de l'appelant 
  ------------------------------------------------------------------------*/
void afficher (int rang, pthread_t thdId) {
  printf("Je suis le thread de rang %d, mon identificateur est %lu\n", rang, thdId);
}

/*------------------------------------------------------------------------
 Fonction d'affichage d'une erreur selon la cause de l'echec d'une primitive
 Arret du thread si arret positionne a 1
  ------------------------------------------------------------------------*/
void thdErreur (char *msg, int cause, int arret) {
  printf("%s : %s \n", msg, strerror(cause));
  if (arret) pthread_exit(NULL);
}

/*------------------------------------------------------------------------
 Code execute par chaque thread 
  ------------------------------------------------------------------------*/

void *thd_afficher (void *arg) {
  int x;
  x = *(int*)arg;

  for (int i = 0; i < nbAffichages; i++)
    afficher(x,pthread_self()); 

  pthread_exit(NULL);
}

/*------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
  int i, nbThreads, etat;
  pthread_t idThreads[NB_THREADS_MAX];

  if (argc != 2) {
    printf("Usage : %s <Nb Threads>\n", argv[0]);
    exit(1);
  }
  nbThreads = atoi(argv[1]);
  if (nbThreads > NB_THREADS_MAX)
    nbThreads = NB_THREADS_MAX;

	int rang[nbThreads];
  printf("Combien d'affichages du message ?\n");
  scanf("%d", &nbAffichages);

  /* Creation des threads */
  for (i = 0; i < nbThreads; i++) {
	  rang[i] = i;
    if ((etat = pthread_create(&idThreads[i], NULL, thd_afficher, (void*)&rang[i])) != 0)
      thdErreur("Echec create", etat, 0);
  }
  /* Attendre la fin des threads  */
  for (i= 0; i < nbThreads; i++) {
    if ((etat = pthread_join(idThreads[i], NULL)) != 0)
      thdErreur("Echec join", etat, 0); 

  }
  return 0;
}
