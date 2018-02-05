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

/** Exercice 2 : */

char * read_one_line(FILE * file){
  if(file==NULL)
    return NULL;
  int lg=1;
  int x;
  char* ch=(char *)malloc(lg);
  char c;
  c=fgetc(file);
  while((c!='\n') && c!=EOF){
    x=lg-1;
    *(ch+x)=c;
    ++lg;
    ch=(char *)realloc(ch,lg);
    c=fgetc(file);
  }
  return ch;
}
    
char * read_input_string(void){ 
  printf("Taper une chaine de caractère\n");
  return read_one_line(stdin);
}

int main_exercise_2(void){
  char * ch = read_input_string();
  printf("%s\n",ch);
  if(ch!=NULL)
    free(ch);
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

/** Exercice 6 : */

int replace_first_occurrence(char * dest, const char * src, const char * before, const char * after){
	dest = (char*)malloc(sizeof(strlen(src))+sizeof(strlen(after))+1);
	char *occurence = strstr(src,before);
	printf("%s\n", occurence);
	int decalage = strlen(before);
	return 0;
}

int main_exercise_6(){
	char *dest = NULL;
	char *src = "Mamie boit son thé";
	char *before = "Mamie";
	char *after = "Papipor";
	replace_first_occurrence(dest, src, before, after);
	
	return 0;
}
int main(int argc, char * argv[])
{
	/* Ne décommenter qu'une seule des lignes suivantes à la fois */

    // return main_exercise_1();
    // return main_exercise_2();
    // return main_exercise_3();
    // return main_exercise_4();
    // return main_exercise_5(argc, argv);
    return main_exercise_6();
    // return main_exercise_7();
    // return main_exercise_8();
    // return main_exercise_9();
}

