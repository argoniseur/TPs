#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int NBO, NBC;
int tabReception[200];
sig_atomic_t x;

typedef struct message_{
	int pid;
	int infos[200000];
}Message;

void erreur (char *msg, int codeRetour) {
  perror(msg);
  exit(codeRetour);
}

void receptionSignal(int sigRecu){
	x = 1;
}

void ouvrier(int num, int tubeReception, int tubeEnvoi){
	Message m;
	int tour = 0;
	while(tour != NBC){
		tour++;
		read(tubeReception, &m, sizeof(Message));
		printf("Ouvrier %d (%d) : Réception de la commande du client %d\n", num, (int)getpid(), m.pid);
		char * affichage = malloc(30000 * sizeof(char));
		char * tmp = malloc(200*sizeof(char));
		sprintf(affichage, "<< numO = %d  ", num);
		sprintf(tmp, "%d", m.pid);
		strcat(affichage, tmp);

		for(int i = 0;i<NBO;i++){
			sprintf(tmp, " infos[%d] = %d", i, m.infos[i]);
			strcat(affichage, tmp);
		}
		strcat(affichage, " >>");
		printf("%s\n", affichage);
		m.infos[num] = num;
		
		if(num == NBO-1){
			kill((pid_t)m.pid, SIGUSR1);
		}

		write(tubeEnvoi, &m, sizeof(Message));
		free(affichage);
		free(tmp);
	}
	close(tubeReception);
	close(tubeEnvoi);
}

void client(int num, int tubeReception, int tubeEnvoi){
	signal(SIGUSR1, receptionSignal);
	Message m;
	m.pid = (int)getpid();
	for(int i = 0; i<NBO;i++){
		m.infos[i] = m.pid;
	}
	printf("\tClient %d (%d): Commande envoyée à l'ouvrier 0\n", num, m.pid);
	write(tubeEnvoi, &m, sizeof(Message));

	while(!x){
		printf("\tClient %d (%d): Je m’occupe en attendant ma commande...\n", num, m.pid);
		sleep(10);
	}
	x = 0;
	printf("\tClient %d (%d): Ma commande est arrivée !\n", num, m.pid);
	read(tubeReception, &m, sizeof(Message));
	close(tubeReception);
	close(tubeEnvoi);
}

int main(int argc, char ** argv){
	if(argc != 3)
		erreur("Usage: ./<program_name> <NBO> <NBC>", 1);

	NBO = atoi(argv[1]);
	NBC = atoi(argv[2]);
	pid_t tabPidO[NBO];
	int tabPipe[NBO+1][2];

	for(int i = 0; i<NBO+1;i++){
		if(pipe(tabPipe[i]) != 0)
			erreur("Pipe", i);
	}


	for(int i=0;i<NBO;i++){
		switch(tabPidO[i] = fork()){
			case -1:
				erreur("Création fils", i);
			case 0:
			
				//close de tous les tubes non concernés en lecture
				for(int j = 0;j<NBO+1;j++){
					if (j != i){
						close(tabPipe[j][0]);
					}
				}
				//close de tous les tubes non concernés en ecriture
				for(int j = 0;j<NBO+1;j++){						
					if(j != i+1){
						close(tabPipe[j][1]);
					}
				}
				printf("\n\n");
				ouvrier(i, tabPipe[i][0], tabPipe[i+1][1]);
				exit(0);
			default:
				break;
		}
	}

	// close de tous les tubes non concernés en lecture par les clients
	for(int j = 0;j<NBO;j++){
		close(tabPipe[j][0]);
	}
	//close de tous les tubes non concernés en ecriture par les clients
	for(int j = 1;j<=NBO+1;j++){
		close(tabPipe[j][1]);
	}

	for(int i=0;i<NBC;i++){
		switch(fork()){
			case -1:
				erreur("Création fils", i);
			case 0:
				client(i, tabPipe[NBO][0], tabPipe[0][1]);
				exit(0);
			default:
				break;
		}
	}
return 0;
}