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
	
	int* M = malloc(sizeof(void));
	int* U = malloc(sizeof(void));
	int N;
	int i = 0, j;	
	
	while(fscanf(fichier, "%c", &cptc) != EOF){
		if(cptc == 'o'){
			M = realloc(M, (i+1)*sizeof(int));
			U = realloc(U, (i+1)*sizeof(int));
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
	
	int x, y;
	for(i = 1;i<N;i++){
		for(j = 0;j<capacite+1;j++){
			x = S[i-1][j-M[i]] + U[i];
			y = S[i-1][j];
			
			if ((x>y) && (j-M[i] >= 0))
				S[i][j] = x;
			else 
				S[i][j] = y;
		}
	}
	for(i = 0;i<N;i++){
		for(j = 0;j<(capacite+1);j++){
			printf("%d ", S[i][j]);
		}
		printf("\n");
	}
	int E[N];
	for(i = 0;i<N;i++){
		E[i] = 0;
	}
	
	i = N-1;
	j = capacite;
	
	for(i = N-1;i>=0;i--){
		if(S[i][j] == S[i-1][j]){
			E[i] = 0;
		}
		else{
			E[i]=1;
			j=j-M[i];
		}
	}
	printf("Contenu du sac:");
	for(i = 0;i<N;i++){
		if(E[i] == 1)
			printf(" %d", i);
	}
	printf("\n");
	fclose(fichier);
	return 0;
}
