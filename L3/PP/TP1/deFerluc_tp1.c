#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>
#define SIZE 20000

int main(int argc, char **argv){
  int i , j;
  double t,start,stop;
  int* matrice_A;
  int resultat = 0;

  // Allocations
  matrice_A = (int*) malloc(SIZE*SIZE*sizeof(int)) ;

  // Initialisations
  for(i = 0; i < SIZE; i++){
    for(j = 0; j < SIZE; j++){
      matrice_A[i*SIZE + j] = (int)rand()/(int)RAND_MAX;
    }
  }

  // Calcul en faisant varier le nombre de threads
  printf("Version séquentielle\n");   
  start = omp_get_wtime();
  for(i = 0; i < SIZE; i++){
    for(j = 0; j < SIZE; j++){
      resultat += matrice_A[i*SIZE + j];
    }
  }
  stop=omp_get_wtime();
  t=stop-start;
  printf("%d\t%f\n",resultat,t);


  int res[4] = {0,0,0,0};
  resultat = 0;
  
  printf("Version parallèle 1\n");   
  start = omp_get_wtime();
  #pragma omp parallel num_threads(4)
  {
	int num = omp_get_thread_num();	
    #pragma omp for private(j, resultat) 
    for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){
        res[num] += matrice_A[i*SIZE + j];
      }
    }
    #pragma omp single
    for (int i = 0;i<4;i++)
		resultat += res[i];
  }
  stop=omp_get_wtime();
  t=stop-start;
  printf("%d\t%f\n",resultat,t);
  
  resultat = 0;
  int resu = 0;
  printf("Version parallèle 2\n");   
  start = omp_get_wtime();
  #pragma omp parallel num_threads(4)
  {
    #pragma omp for private(j, resu) 
    for(i = 0; i < SIZE; i++){
	  resu = 0;
      for(j = 0; j < SIZE; j++){
        resu += matrice_A[i*SIZE + j];
      }
      #pragma omp atomic
      resultat += resu;
    }
  }
  stop=omp_get_wtime();
  t=stop-start;
  printf("%d\t%f\n",resultat,t);
  
  int reduc = 0;
  printf("Version parallèle 3\n");   
  start = omp_get_wtime();
  #pragma omp parallel num_threads(4)
  {
    #pragma omp for private(j) reduction(+:reduc)
    for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){
        reduc += matrice_A[i*SIZE + j];
      }
    }
  }
  stop=omp_get_wtime();
  t=stop-start;
  printf("%d\t%f\n",reduc,t);
  // Liberations
  free(matrice_A);
  return EXIT_SUCCESS;
}
