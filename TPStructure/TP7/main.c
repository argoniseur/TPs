#include <stdio.h>
#include <stdlib.h>
#include "arbreGRD.h"
#include "queue.h"

int main (int argc, char ** argv){
	GRDTree myT,myT2;
	myT = creerArbre();
  
	printf("Ajout successif de 4,6,2,3,5,7,1\n");
	ajouterEntier(&myT,4);
	ajouterEntier(&myT,6);
	ajouterEntier(&myT,2);
	ajouterEntier(&myT,3);
	ajouterEntier(&myT,5);
	ajouterEntier(&myT,7);
	ajouterEntier(&myT,1);
  
	printf("Affichage de l'arbre :\n");
	triGRD(myT);
	printf("\n");
	deleteTree(myT);
  
	myT2=creerArbre();
  
	printf("Ajout successif de 1,2,3,4,5,6,7\n");
	ajouterEntier(&myT2,1);
	ajouterEntier(&myT2,2);
	ajouterEntier(&myT2,3);
	ajouterEntier(&myT2,4);
	ajouterEntier(&myT2,5);
	ajouterEntier(&myT2,6);
	ajouterEntier(&myT2,7);
  
	printf("Affichage de l'arbre :\n");
	triGRD(myT2);
	printf("\n");
	deleteTree(myT2);

	/* ****************************************** Partie 2 ******************************************** */
	
	GRDTree t;
	int symbole;
	Queue q;
  
	FILE *f_in;

	if (argc<2 || argc>2){	
		printf("Il faut rentrer un fichier (qui sera créé) dans lequel ranger les valeurs saisies\n");
		return 1;
	}

	f_in = fopen(argv[1],"w");
	if (f_in == NULL){
		printf("Ecriture impossible dans %s\n",argv[1]);
		return 2;
	}

	init_Queue(&q);
	t = creerArbre();
	printf("entrez des nombres, tapez -1 pour arreter \n");
	symbole = saisir(&q);
	vider_Tampon(&t,&q,symbole);
	int donnees = -1;
	do{
		donnees = vider_Arbre(&t,&q);
		for (int i = 0;i<5;i++)
			vider_queue(f_in,&q);
	}while(donnees);
	
	return 0; 
}
