/* Compilation : gcc -c boucler.c pour créer boucler.o */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void boucler(void) {
  printf("Processus (fils) de pid %d : Je boucle...\n", getpid());
  sleep(1);
}
