/* 
   Base : synchronisation pour un affichage alterné
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>

#define NB_THREADS_MAX  20
#define NB_MSG           5 // Valeurs a changer si necessaire 
#define NB_LIGNES        2

typedef struct {
  int nbLignes;
  int nbMsg;
} Parametres;

int nbThreads;
pthread_mutex_t mutex[NB_THREADS_MAX];

//---------------------------------------------------------------------
// Afficher un message d'erreur en fonction du code erreur obtenu
void thdErreur(int codeErr, char *msgErr, void *codeArret) {
  fprintf(stderr, "%s: %d soit %s \n", msgErr, codeErr, strerror(codeErr));
  pthread_exit(codeArret);
}

//---------------------------------------------------------------------
// Synchronisation a ecrire 
// Demander a acceder a l'ecrani : a eventuellement parametrer
void demanderAcces(int i) {
	pthread_mutex_lock(&mutex[i]);
};

// Liberer l'acces a l'ecran : a eventuellement parametrer
void libererAcces(int i) {
	pthread_mutex_unlock(&mutex[(i+1)%nbThreads]);
	
};

//---------------------------------------------------------------------
// Fonction executee par un thread : afficher un message un certain nombre
// de messages (nbMsg) a l'ecran constiotues de nbLignes lignes
void *thd_afficher (void *arg) {
  int i, j, etat;
  Parametres param = *(Parametres *)arg;
  int s1, s2;

  for (i = 0; i < param.nbMsg; i++) {
    // Acceder a l'ecran pour afficher son message 
    demanderAcces(param.nbLignes - 2);

    for (j = 0; j < param.nbLignes; j++) {
      printf("Afficheur(%lu), j'affiche Ligne %d/%d - Msg %d/%d \n", 
             pthread_self(), j, param.nbLignes, i, param.nbMsg);
      usleep(10); // Temporiser un peu
    } 

    // Rendre l'acces a l'ecran pour le suivant
    libererAcces(param.nbLignes - 2);
    }
  printf("Thread %lu, je me termine \n", pthread_self());
  /* Se terminer sans renvoyer de compte-rendu */
  pthread_exit((void *)NULL);
}

//---------------------------------------------------------------------


int main(int argc, char*argv[]) {
  pthread_t idThdAfficheurs[NB_THREADS_MAX];
  Parametres param[NB_THREADS_MAX];
  int i, etat;

  if (argc != 2) {
    printf("Usage : %s <Nb de threads>\n", argv[0]);
    exit(1);
  }
  
  for(int i = 0;i<NB_THREADS_MAX;i++)
	pthread_mutex_init(&mutex[i],NULL);
  for(int i = 1;i<NB_THREADS_MAX;i++)
	demanderAcces(i);
	
  nbThreads = atoi(argv[1]);
  if (nbThreads > NB_THREADS_MAX)
    nbThreads = NB_THREADS_MAX;

  // Lancer les threads afficheurs
  for (i = 0; i < nbThreads; i++) {
    param[i].nbLignes = NB_LIGNES + i;
    param[i].nbMsg = NB_MSG;
    if ((etat = pthread_create(&idThdAfficheurs[i], NULL, thd_afficher, &param[i])) != 0)
      thdErreur(etat, "Creation afficheurs", NULL);
  }

  // Attendre la fin des threads afficheur car si le thread principal
  // - i.e. le main() - se termine, les threads crees meurent aussi
  for (i = 0; i < nbThreads; i++) {
    if ((etat = pthread_join(idThdAfficheurs[i], NULL)) != 0)
      thdErreur(etat, "Join threads afficheurs", NULL);
  }

  printf ("\nFin de l'execution du thread principal \n");
  return 0;
}
