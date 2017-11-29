#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char ** argv){
		struct sigaction action, old;
		pid_t pid;
			
		action.sa_handler = SIG_IGN;
		sigemptyset(&action.sa_mask);
		action.sa_flags = 0;
		sigaction(SIGINT, &action, &old);
		switch(pid = fork()){
			case -1:
				perror("Y a une couille dans le paté\n");
				exit(99);
				
			case 0:
				while (1){
					printf("Je suis le processus fils de pid %d, mon père de pid %d s’est protégé contre SIGINT, je le suis aussi\n", (int)getpid(), (int)getppid());
					sleep(1);
				}
				exit(1);
				
			default:
				wait(NULL);
				break;
		}			
	return 0;
}
