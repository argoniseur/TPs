#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LONG_MAX_NOM 20

typedef struct
{
	char Nom[LONG_MAX_NOM+1];
	int Age;
	int NbEnfants;
}Infos;

/***************************************************************************************/

void vider_buffer()
{
	char c;
	do scanf("%c", &c);
	while(c != '\n' && c != EOF);
}

/***************************************************************************************/

Infos SaisieInfos()
{
	Infos personne;
	printf("Nom (< a %d caracteres): ", LONG_MAX_NOM);
	scanf("%s", personne.Nom);

	printf("Age: ");
	scanf("%d", &(personne.Age));

	printf("Nombre d'enfants: ");
	scanf("%d", &(personne.NbEnfants));

	return personne;
}

/***************************************************************************************/

int Creation()
{
	char NomFichier[100];
	printf("Nom du fichier a creer: ");
	scanf("%s", NomFichier);

	int fichier = open(NomFichier, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
	int nbFiches, i;
	Infos info; 
	if (fichier == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return 2;
	}
	
	printf("Nombre de fiches à entrer: ");
	scanf("%d", &nbFiches);
	
	for (i=1;i<=nbFiches;i++)
	{	
		printf("Fiche %d\n", i);	
		info = SaisieInfos();
		write(fichier, &info, sizeof(Infos));
	}

	if (close(fichier) == -1)
	{
		perror("Erreur lors de la fermeture");
		return 5;
	}
	return 0;
}

/***************************************************************************************/

int Consultation(char NomFichier[], int nFich)
{
	int fichier = open(NomFichier, O_RDONLY);
	int nblu;
	Infos info; 
	if (fichier == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return 2;
	}
	lseek(fichier,(nFich-1)*sizeof(Infos),SEEK_SET);
	if ((nblu = read(fichier,&info,sizeof(Infos))) == sizeof(Infos)){
		printf("Nom : %s\n", info.Nom);
		printf("Age : %d\n", info.Age);
		printf("Nombre d'enfants : %d\n", info.NbEnfants);
	}
	else if(nblu == -1)
		perror("Erreur de lecture");
	return 0;
}

/***************************************************************************************/

int main(int argc, char * argv[])
{
	int choix, code_erreur, nFich;
	printf("Selection:\n");
	printf("1 - Création de fiches\n");
	printf("2 - Consultation de fiches\n");
	scanf("%d", &choix);
	if (choix == 1){
		code_erreur = Creation();
	}
	else if(choix == 2){
		char nom[LONG_MAX_NOM+10];
		printf("Nom du fichier à consulter:\n");
		scanf("%s", &nom);
		printf("Numéro de la fiche à consulter:\n");
		scanf("%d", &nFich);
		Consultation(nom, nFich);
	}
	return 0;
}
