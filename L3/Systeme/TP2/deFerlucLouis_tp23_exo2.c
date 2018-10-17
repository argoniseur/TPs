#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "boucler.h"

void erreur (char *msg, int codeRetour) {
  perror(msg);
  exit(codeRetour);
}

int main(int argc, char ** argv){
	int N;
	if(argc != 2)
		erreur("arguments", 1);
		
	N = argv[1];
	int tabPipe[N][2];
return 0;
}
