#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {

	if (argc != 2) {
		printf("Un seul paramètre autorisé");
		exit(4);
	}
	char* fichierO = argv[1];
	pid_t pid, pid2, pid3;
	int status;
	if ((pid=fork()) == -1){
		perror("Erreur de création du fils");
		exit(5);
	}
	if (!pid){
		//fils
		if (execlp("gcc","gcc","-c", argv[1], NULL )) {
		
			
		}
		perror("Fils 1 atteint !\n");
		exit(1);
	}
	if (pid){
		wait(&status);
		if (WIFEXITED (status)){
			int len = strlen(fichierO);
			fichierO[len-1] = 'o';
	
			char* executable = "lancerSupp";
			//argument = ("%s -o %s", fichierO, executable);
			if ((pid2=fork()) == -1){
				perror("Erreur de création du fils");
				exit(6);
			}
			if (!pid2){
				
				if (execlp("gcc","gcc", fichierO,"-o",executable,NULL)) {
					
				}
				perror("Fils 2 atteint !\n");
				exit(2);
			}
			if (pid2){
				wait(&status);
				if (WIFEXITED (status)){
					if ((pid3=fork()) == -1){
						perror("Erreur de création du fils");
						exit(7);
					}
					if (!pid3){
						execlp(executable,executable,NULL);
						perror("Fils 3 atteint !\n");
						exit(3);
					}
					if (pid){
						wait(&status);
						if (WIFEXITED (status)){
							printf("pere 3 fini\n");
						}
					}
				}
			}
		}
	}
return 0;
}
