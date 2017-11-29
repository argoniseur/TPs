#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main(int argc, char ** argv){
	char message[3] = "765";
	char *messRecons;
	pid_t pid;
	char C;
	
	int T[2];
	if (pipe(T) == -1) {
		perror("Probleme creation tube");
		exit(99);
	}
		
	int numBoucle = atoi(argv[1]);
	for(int i = 1; i <= numBoucle; i++){
	
	
		switch(pid = fork()){
			case -1:
				printf("Erreur");
				exit(98);
				
				
			case 0:
				/* Fils lecteur */
				close(T[1]);
				/* Fils lit */
				while (read (T[0], &C, sizeof(int))) {
					messRecons = (int)&C;
				}
				printf("Je suis le processus de pid %d, n°%d dans l’anneau, j’ai reçu de %d, j’envoie au n°%d l’info [%d – %s – %d]\n", (int)getpid(), i, (int)getppid(), i+1, (int)getpid(), messRecons, i);
				close(T[0]);
				exit(1);				
				break;
			
			
			
			default:
				printf("Je suis le processus de pid %d, n°%d dans l’anneau, j’envoie au n°%d l’info [%d – %s – %d]\n", (int)getpid(), i, i+1, (int)getpid(), message, i);
				/* Pere redacteur */
				close(T[0]);
				write(T[1],message,strlen(message));
				close(T[1]);
				/* Pere attend */
				wait(NULL);
				/* Pere se termine */
				printf("Je suis le processus de pid %d, je me termine aussi\n", (int)getpid());
				exit(1);
				break;
		}
		
	}
	
	
	return 0;
}
