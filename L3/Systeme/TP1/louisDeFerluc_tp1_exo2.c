/**-------------------------------------------------------------------------
  TP1 - Squelette code exercice 1-V2
  Compilation : gcc nomFic.c -o nomFic -lpthread
--------------------------------------------------------------------------**/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NB_THREADS_MAX  10
#define NB_FOIS         10

/*------------------------------------------------------------------------
 * Affichage de l'identite de l'appelant 
  ------------------------------------------------------------------------*/
void afficher (int rang, pthread_t thdId, int retour) {
  printf("Thread compagnon de rang %d, identifié par %lu, je mourrais en retournant %d\n", rang, thdId, retour);
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
	int* y = malloc(sizeof(int));
	*y = rand()%10;

    afficher(x,pthread_self(),*y); 

  pthread_exit((void*)y);
}

/*------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
  int i, nbThreads, etat, somme;
  int* retVal;
  pthread_t idThreads[NB_THREADS_MAX];
	srand(time(NULL));
  if (argc != 2) {
    printf("Usage : %s <Nb Threads>\n", argv[0]);
    exit(1);
  }
  nbThreads = atoi(argv[1]);
  if (nbThreads > NB_THREADS_MAX)
    nbThreads = NB_THREADS_MAX;

	int rang[nbThreads];

  /* Creation des threads */
  for (i = 0; i < nbThreads; i++) {
	  rang[i] = i;
    if ((etat = pthread_create(&idThreads[i], NULL, thd_afficher, (void*)&rang[i])) != 0)
      thdErreur("Echec create", etat, 0);
  }
  /* Attendre la fin des threads  */
  somme = 0;
  for (i= 0; i < nbThreads; i++) {
    if ((etat = pthread_join(idThreads[i], (void **)&retVal)) != 0)
      thdErreur("Echec join", etat, 0); 
    
    printf("Thread principal %lu: valeur retournée par le thread %lu = %d\n", pthread_self(), idThreads[i],*retVal);

	somme = somme + *retVal;
  }
  printf("Thread principal %lu: somme des valeurs reçues = %d\n", pthread_self(),somme);
  return 0;
}
