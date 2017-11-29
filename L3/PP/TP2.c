#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv){
	
	if (argc != 2){
		fprintf(stderr, "Usage: %s fichier\n", argv[0]);
		exit(99);
	}
	
	FILE* fichier = NULL;
	fichier = fopen(argv[1],"r");
	if(fichier == NULL){
		fprintf(stderr,"Erreur d'ouverture du fichier");
		exit(98);
	}
	char cptc;
	int capacite;
	
	/* On récupère la capacité du sac. Elle servira à définir les tableaux M et U */
	fscanf(fichier, "%c", &cptc);
	fscanf(fichier, "%d", &capacite);
	
	printf("%d\n", capacite);
	int* M = malloc(sizeof(void));
	int* U = malloc(sizeof(void));
	int N;
	int i = 0;	
	
	while(fscanf(fichier, "%c", &cptc) != EOF){
		if(cptc == 'o'){
			M = realloc(M, (i+1)*sizeof(int));
			M = realloc(U, (i+1)*sizeof(int));
			fscanf(fichier, "%d", &M[i]);
			fscanf(fichier, "%d", &U[i]);
			i++;
		}
	}
	N = i;
	int S[N][capacite+1];
	
	for(i = 0;i<capacite+1;i++){
		if(M[0] <= i)
			S[0][i] = U[0];
		else
			S[0][i] = 0;
	}
	for(i = 0;i<capacite+1;i++){
		
		printf("%d ", S[0][i]);
	}

	for(i = 0;i<N;i++){
		
		printf("%d %d\n", M[i], U[i]);
	}
		
	fclose(fichier);
	return 0;
}
