/** @file
 * @author Louis de Ferluc (Groupe de TP 2.2)
 * @brief Fichier source pour le TP 4 "Chaînes de caractères (dynamiques)"
 * @note Ce fichier contiendra la totalité de votre code pour ce TP.
 */
#include "tp_string.h"




/** @todo Indiquez votre prénom, votre nom et votre groupe en face de la balise @b @@author en haut de ce fichier. */
/* Votre code ici */

/** Exercice 1 : Fonction concat et fonction main_exercise_1 */
char* concat(char* ch1, char* ch2){
	char* ch3 = (char*)malloc(sizeof(char)*(strlen(ch1) + strlen(ch2)) + 1);
	strcpy(ch3,ch1);
	strcat(ch3,ch2);
	return ch3;
}

int main_exercise_1(){
	char* chaine1 = "Salut";
	char* chaine2 = " Patrick";
	char* chaine3 = concat(chaine1, chaine2);
	printf("%s\n", chaine3);
	free(chaine3);
	return 0;
}

/** Exercice 3 : */

void swap_static_strings(char (*lhs)[STATIC_STRING_LENGTH], char (*rhs)[STATIC_STRING_LENGTH]){
	char ch3[STATIC_STRING_LENGTH];
	strcpy(ch3,*lhs);
	strcpy(*lhs,*rhs);
	strcpy(*rhs,ch3);
}

void swap_dynamic_strings(char* (*lhs), char* (*rhs)){
	char* ch3 = *lhs;
	*lhs = *rhs;
	*rhs = ch3;
}

int main_exercise_3(){
	char* chaine1 = "Salut";
	char* chaine2 = " Patrick";
	swap_dynamic_strings(&chaine1, &chaine2);
	printf("%s --- %s\n", chaine1, chaine2);
	return 0;
}

int main(int argc, char * argv[])
{
	/* Ne décommenter qu'une seule des lignes suivantes à la fois */

    // return main_exercise_1();
    // return main_exercise_2();
    return main_exercise_3();
    // return main_exercise_4();
    // return main_exercise_5(argc, argv);
    // return main_exercise_6();
    // return main_exercise_7();
    // return main_exercise_8();
    // return main_exercise_9();
}

