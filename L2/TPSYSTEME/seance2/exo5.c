#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define NBMOTSMAX 20

int decoupe(char Chaine[], char *pMots[])
{
  char *p;
  int NbMots=0;

  p=Chaine; /* On commence par le debut */
  /* Tant que la fin de la chaine n'est pas atteinte et qu'on ne deborde pas */
  while ((*p)!='\0' && NbMots<NBMOTSMAX)
  {
    while ((*p)==' ' && (*p)!='\0') p++; /* Recherche du debut du mot */
    if ((*p)=='\0') break; /* Fin de chaine atteinte */
    pMots[NbMots++]=p; /* Rangement de l'adresse du 1er caractere du mot */
    while ((*p)!=' ' && (*p)!='\0') p++; /* Recherche de la fin du mot */
    if ((*p)=='\0') break; /* Fin de chaine atteinte */
    *p='\0'; /* Marquage de la fin du mot */
    p++; /* Passage au caractere suivant */
  }
  pMots[NbMots]=NULL; /* Derniere adresse */
  return NbMots;
}
int main(int argc, char * argv[])
{
	char *pMots[NBMOTSMAX+1];
	int i, status;
	pid_t pid;
	for (i=1;i<argc;i++)
	{
		pid = fork();
		switch(pid)
		{
		case -1:
			perror("Fils non cree!");
			exit(1);
			break;
		case 0:
			
			printf("[%d] Je lance %s:\n", getpid(), argv[i]);
			decoupe(argv[i],pMots);
			execvp(pMots[0],pMots);
			exit(2);
			break;
		default:
			printf("[%d] J'ai delegue %s a %d. J'attends sa fin...\n", getpid(), argv[i], pid);
			wait(&status);
			if (WIFEXITED (status))
			{
        			printf("[%d] %d termine.\n", getpid(), pid);
			}
			break;
		}
	}
	printf("[%d] J'ai fini.\n", getpid());


	return 0;
}
