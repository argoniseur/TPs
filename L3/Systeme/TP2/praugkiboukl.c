#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void boucler(void) {
  printf("Processus de pid %d : Je boucle...\n", getpid());
  sleep(1);
}

int main(void){
	while(1)
		boucler();
	return 0;
}
