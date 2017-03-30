#include "liste_doublement_chainee.h"

/* Vide le buffer de fgets */
void viderBuffer(){
	int c = 0;
	while (c != '\n' && c != EOF)
		c = getchar();
}

Element build_element(char* c, int x){
	Element e = (Element)malloc(sizeof(int)+100*sizeof(char));

	e->valeur = (unsigned int)x;

	e->chaine = c;

	return e;
}

int main(int argc, char ** argv){
	ListeDouble liste = initialiser_liste();

	/* Insérer */

	int x;
	char c[100];
	char* tmp;
	printf("Note: ");
	scanf("%d", &x);

	viderBuffer();
	printf("Nom: ");
	fgets(c,100,stdin);
	
	tmp = strchr(c, '\n');

	*tmp = '\0';

	Element e = build_element(c,x);

	liste = ajoute_element(liste,e);
	liste = ajoute_element(liste,e);
	liste = ajoute_element(liste,e);
	liste = ajoute_element(liste,e);
	liste = ajoute_element(liste,e);

	imprimer_liste_croissant(liste,true);
	return 0;
}
