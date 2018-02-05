#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void info_p_courant(pid_t pid)
{
	char* p;
	char c[6];
	int status;
	p = getlogin();
	if(pid)
	{
		sleep(1);
		strcpy(c,"[PERE]");
	}
	else
	{
		strcpy(c,"[FILS]");
	}
	printf("%s PID: %d\n", c, getpid());
	printf("%s PID pere: %d\n", c, getppid());
	printf("%s Groupe: %d\n", c, getpgrp());
	printf("%s User: %s\n", c, p);
	printf("%s Id User: %d\n", c, getuid());
	printf("%s ID User's group: %d\n", c, getgid());
	if(!pid)
	{
		printf("Fils termine. Status = 2\n");
		exit(2);
	}
	else
	{
		wait (&status) ;
      		if (WIFEXITED (status))
		{
        		printf ("fils termine normalement: status = %d\n", WEXITSTATUS(status));
			printf("Pere termine. Status = 3\n");
			exit(3);	
		}
      		else
		{
        		printf ("fils termine anormalement\n") ;
			printf("Pere termine. Status = 3\n");
			exit(3);
		}
	}
}

/*********************************************************/

int main(void)
{
	pid_t pid;
	if ((pid=fork()) == -1)
	{
		perror("Fils non cree");
		exit(1);
	}
	info_p_courant(pid);






	return 0;
}
