/*
 * TP4 - Squelette exercice 4 - Modele des producteurs-consommateurs
 * Objectif de la synchronisation : Que les depots et retraits se
 * fassent de maniere coherente dans un buffer partage gere de facon
 * circulaire. Les retraits se font dans l'ordre des depots
 *
 * Variables partagees : buffer, indices de depôts et de retraits
 *  
 * Pour tester avec la temporisation par usleep, il faut definir
 * la constante lors de la compilation grace a l'option -D :
 * gcc tp45_exo4_base.c -oexo4b -DTEMPO -lpthread -Wall
 * Rappel : Votre synchronisation doit marcher avec ou sans cette
 * temporisation
 * Pour afficher le contenu du buffer : -DTRACE_BUFFER
 * Pour afficher les demandes des prod/conso : -DTRACE_DMDES
 * Pour afficher les creations de threads prod/conso : -DTRACE_CREAT
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define NB_PROD_MAX   15
#define NB_CONSO_MAX  15

#define NB_CASES_MAX  20 

typedef struct
  {
  char info[80];
  int  type;              // Ne sert pas dans cette version de base
  } TypeMessage;          // (sera mis a zero)

typedef struct 
  {
  TypeMessage tampon[NB_CASES_MAX]; // Buffer partage
  int iDepot;             // Indice du prochain depot
  int iRetrait;           // Indice du prochain retrait
  } TypeBuffer;

/* Variables partagees par les threads producteurs et consommateurs */
TypeBuffer leBuffer;   // Tampon circulaire 
int nbCases;           // Nombre de cases effectif du buffer
int nbDepots,    // Nombre de depots faits par chaque producteur
    nbRetraits;  // Nombre de retraits faits par chaque consommateur
//
// A completer : semaphore(s) et variables partagees utile(s)
//
sem_t semDepot, semRetrait, semMsg;
int nbMsgEffectifs = 0;
//-----------------------------------------------------------
// Affichage erreur liee a l'echec d'un appel a une fonction pthread_
// codeErr = code de retour de la fonction testee
// codeArret = adresse de l'information retournee lors du pthread_exit
// Mettre NULL si cette information n'a pas d'importance
void thdErreur(int codeErr, char *msgErr, void *codeArret) {
  fprintf(stderr, "%s: %d soit %s \n", msgErr, codeErr, strerror(codeErr));
  pthread_exit(codeArret);
}

//-----------------------------------------------------------
// Fonction pour perdre un peu de temps
void attenteAleatoire (void) {
#ifdef TEMPO	
    usleep(rand()%100);	  
#endif
}

//-----------------------------------------------------------
// Afficher le contenu du buffer partage
void afficherBuffer (void) {
  int i;

  printf("\t\tBuffer : [ ");
  for (i = 0; i < nbCases; i++)
    printf("%s %d", leBuffer.tampon[i].info, i);
    // Affichage si on gere le type de message
    //printf("%s/%d ", leBuffer.tampon[i].info, leBuffer.tampon[i].type);
  printf(" ]");
}

//-----------------------------------------------------------
// Operation elementaire de depot dans la prochaine case vide
void depot (TypeMessage leMessage) {
  strcpy(leBuffer.tampon[leBuffer.iDepot].info, leMessage.info);
  leBuffer.tampon[leBuffer.iDepot].type = leMessage.type;
  leBuffer.iDepot = (leBuffer.iDepot + 1) % nbCases;
}

//-----------------------------------------------------------
// Operation elementaire de retrait de la prochaine case pleine
void retrait (TypeMessage *leMessage) {
  strcpy(leMessage->info, leBuffer.tampon[leBuffer.iRetrait].info);
  leMessage->type =  leBuffer.tampon[leBuffer.iRetrait].type;
  leBuffer.iRetrait = (leBuffer.iRetrait + 1) % nbCases;
}
  
/* 
 * Synchronisation a completer : faire un depot et un retrait
 */
//-----------------------------------------------------------
// Appele par un producteur pour deposer de maniere sure un
// message (le rang du producteur est passe pour la trace)
void deposer (TypeMessage unMessage, int rangProd) {
  
  sem_wait(&semDepot);
  sem_wait(&semMsg);
  depot(unMessage);  
  printf ("\tProd %d (%lu) : Message depose = %s\n", rangProd, pthread_self(), unMessage.info);
  sem_post(&semMsg);
  sem_post(&semRetrait);

#ifdef TRACE_BUFFER    
  afficherBuffer();
  printf("\n");
#endif
}

//-----------------------------------------------------------
// Appele par un consommateur pour retirer de maniere sure un
// message (le rang du consommateur est passe pour la trace)
void retirer (TypeMessage *unMessage, int rangConso) {	
  sem_wait(&semRetrait);
  sem_wait(&semMsg);
  retrait(unMessage);
  printf ("\t\tConso %d (%lu) : Message retire = %s\n", rangConso, pthread_self(), unMessage->info);
  sem_post(&semMsg);
  sem_post(&semDepot);
  
#ifdef TRACE_BUFFER    
  afficherBuffer();
  printf("\n");
#endif
}

//-----------------------------------------------------------
// Comportement d'un producteur
void * producteur(void *arg) {
  int i;
  TypeMessage leMessage;
  int rang = *(int *)arg;

  srand(pthread_self());

  for (i = 0; i < nbDepots; i++) {
    attenteAleatoire();

    // Preparer le message	  
    sprintf (leMessage.info, "%s %d %s %d", "Bonjour", i+1, "de prod", rang);
    leMessage.type = 0;

#ifdef TRACE_DMDES
    printf ("Prod %d (%lu) : Depot %d, message = %s \n", rang, pthread_self(), i+1, leMessage.info);
#endif
    // Le deposer
    deposer(leMessage, rang);
  }
  pthread_exit(NULL);
}

//-----------------------------------------------------------
// Comportement d'un consommateur
void * consommateur(void *arg) {
  int i;
  TypeMessage leMessage;
  int rang = *((int *)arg);

  srand(pthread_self());

  for (i = 0; i < nbRetraits; i++) {
    attenteAleatoire();

    // Retirer le 1er message disponible
    retirer(&leMessage, rang);
    // L'afficher
#ifdef TRACE_DMDES
    printf ("Conso %d (%lu) : Retrait %d, message lu = %s \n", rang, pthread_self(), i+1, leMessage.info);
#endif
#ifdef TRACE_BUFFER    
    afficherBuffer();
    printf("\n");
#endif
  }
  pthread_exit(NULL);
}

//-----------------------------------------------------------
int main(int argc, char *argv[]) {
  int i, etat;
  //int nbThds;
  int nbProd, nbConso;
  int rangThds[NB_PROD_MAX + NB_CONSO_MAX];
  pthread_t idThdProd[NB_PROD_MAX], idThdConso[NB_CONSO_MAX];

  if (argc < 5) {
    printf ("Usage: %s <Nb Prod <= %d> <Nb Conso <= %d> <NB depots/prod> <Nb retraits/conso> <Nb Cases <== %d> \n", 
             argv[0], NB_PROD_MAX, NB_CONSO_MAX, NB_CASES_MAX);
    exit(2);
    }

  nbProd  = atoi(argv[1]);
  if (nbProd > NB_PROD_MAX)
    nbProd = NB_PROD_MAX;
  nbConso = atoi(argv[2]);
  if (nbConso > NB_CONSO_MAX)
    nbConso = NB_CONSO_MAX;
  //nbThds = nbProd + nbConso;
  nbDepots = atoi(argv[3]);
  nbRetraits = atoi(argv[4]);
  nbCases = atoi(argv[5]);
  if (nbCases > NB_CASES_MAX)
    nbCases = NB_CASES_MAX;

  /* Initialiser le(s) semaphore(s) */
  if (sem_init(&semDepot, 0, nbCases) != 0){
		printf("\n mutex init failed\n");
		exit(99);
  }
  if (sem_init(&semRetrait, 0, 0) != 0){
		printf("\n mutex init failed\n");
		exit(99);
  }
  if (sem_init(&semMsg, 0, 1) != 0){
		printf("\n mutex init failed\n");
		exit(99);
  }

  /* Creation des nbProd producteurs et nbConso consommateurs */
  for (i = 0; i <  nbProd; i++) {
    rangThds[i] = i;
    if ((etat = pthread_create(&idThdProd[i], NULL, producteur, &rangThds[i])) != 0)
      thdErreur(etat, "Creation producteur", NULL);
#ifdef TRACE_CREAT
    printf("Creation thread de rang %d -> Prod %d/%d\n", i, rangThds[i], nbProd);
#endif
  }
  for (i = 0; i <  nbConso; i++) {
    rangThds[i+nbProd] = i;
    if ((etat = pthread_create(&idThdConso[rangThds[i]], NULL, consommateur, &rangThds[i+nbProd])) != 0)
      thdErreur(etat, "Creation consommateur", NULL);
#ifdef TRACE_CREAT
    printf("Creation thread de rang %d -> Conso %d/%d\n", i+nbProd, rangThds[i+nbProd], nbConso);
#endif
  }

  /* Attente de la fin des threads */
  for (i = 0; i < nbProd; i++)
    if ((etat = pthread_join(idThdProd[i], NULL)) != 0)
      thdErreur(etat, "Join threads producteurs", NULL);

  for (i = 0; i < nbConso; i++)
    if ((etat = pthread_join(idThdConso[i], NULL)) != 0)
      thdErreur(etat, "Join threads consommateurs", NULL);

  /* Detruire le(s) semaphore(s) */
  sem_destroy(&semDepot);
  sem_destroy(&semRetrait);
  sem_destroy(&semMsg);  
  printf ("\nFin de l'execution du main \n");

  return 0;
}
  
