#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "boucler.h"

typedef struct struct_{
	pid_t pid;
	int valImu;
	int increment;
}Struct;

void erreur (char *msg, int codeRetour) {
  perror(msg);
  exit(codeRetour);
}

int main(int argc, char ** argv){
	int N, nbLus = 0;
	if(argc != 2)
		erreur("arguments", 99);
		
	N = atoi(argv[1]);
	int tabPipe[N][2];
	pid_t tabPID[N];
	
	for(int i=0;i<N;i++){
		if(pipe(tabPipe[i]) != 0)
			erreur("Pipe", i);
	}
	printf("%d\n\n\n",N);
	for(int i=0;i<N;i++){
		switch(tabPID[i] = fork()){
			case -1:
				erreur("Création fils", i);
			case 0:
				//close de tous les tubes non concernés en ecriture
				for(int j = 0;j<N;j++){
					if (j != i)
						close(tabPipe[j][1]);
				}
				//close de tous les tubes non concernés en lecture
				for(int j = 0;j<N;j++){
					if(j != (i-1)%N)
						close(tabPipe[j][0]);
				}
				Struct* maStruct = malloc(sizeof(Struct*));
				//Si on est dans le premier processus on initie la boucle
				if (i == 0){
					while(tabPID[i+1] == 0){
					}
					maStruct->pid = tabPID[i+1];
					maStruct->valImu = 765;
					maStruct->increment = 1;
					
					write(tabPipe[i][1],&maStruct,sizeof(Struct*));
					close(tabPipe[i][1]);
					
					printf("Processus de pid %d, n°%d dans l'anneau: j'envoie au n°%d l'info [ %d - %d - %d ]\n", getpid(), i+1, i+2, (int)maStruct->pid, maStruct->valImu, maStruct->increment);
					
					while((nbLus = read(tabPipe[(i-1)%N][0], &maStruct, sizeof(Struct*))) > 0){
						printf("Je recois . . . %d\n",i);
					}
					close(tabPipe[(i-1)%N][0]);
				}else{
					while((nbLus = read(tabPipe[(i-1)%N][0], &maStruct, sizeof(Struct*))) > 0){
						printf("Je recois . . . %d\n",i);
					}
					close(tabPipe[(i-1)%N][0]);
					
					printf("Processus de pid %d, n°%d dans l'anneau: j'envoie au n°%d l'info [ %d - %d - %d ]\n", getpid(), i+1, ((i+1)%N)+1, (int)maStruct->pid, maStruct->valImu, maStruct->increment);
					
					maStruct->pid = tabPID[i+1];
					maStruct->increment += 1;
					
					write(tabPipe[i][1],&maStruct,sizeof(Struct*));
					close(tabPipe[i][1]);
				}
			default:
				break;
				
		}
	}
	
return 0;
}
