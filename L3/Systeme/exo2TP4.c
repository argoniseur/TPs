#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t sem[3];

void demanderAcces(int i){
	sem_wait(&sem[i]);
}

void libererAcces(int i){
	sem_post(&sem[i]);
}

void* P1 (void *arg){
	for(int i = 0;i<10;i++){
		printf("A");
		libererAcces(1);
		libererAcces(2);
		demanderAcces(0);
		demanderAcces(0);
		printf("B\n");
	}
	pthread_exit((void *)NULL);
}

void* P2 (void *arg){
	for(int i = 0;i<10;i++){
		demanderAcces(1);
		printf("C");
		libererAcces(0);
	}
	pthread_exit((void *)NULL);
}

void* P3 (void *arg){
	for(int i = 0;i<10;i++){
		demanderAcces(2);
		printf("D");
		libererAcces(0);
	}
	pthread_exit((void *)NULL);
}


int main(int argc, char ** argv){
	pthread_t idThdAfficheurs[3];
	int etat;

	for(int i = 0;i<3;i++){
		if(sem_init(&sem[i],0,0)!=0){
			perror("Erreur init semaphore");
			exit(2);
		}
	}
	
	if ((etat = pthread_create(&idThdAfficheurs[0], NULL, P1, NULL)) != 0)
		perror("Erreur thread 1");
		
	if ((etat = pthread_create(&idThdAfficheurs[1], NULL, P2, NULL)) != 0)
		perror("Erreur thread 2");
	
	if ((etat = pthread_create(&idThdAfficheurs[2], NULL, P3, NULL)) != 0)
		perror("Erreur thread 3");



	for (int i = 0; i < 3; i++) {
		if ((etat = pthread_join(idThdAfficheurs[i], NULL)) != 0)
			perror("Join threads afficheurs");
	}
	
	
	return 0;
}
