#include <stdio.h>
#include <stdlib.h>

#include "skiplist.h"


void usage(const char *command) {
	printf("usage : %s -id num\n", command);
	printf("where id is :\n");
	printf("\tc : construct and print the skiplist with data read from file test_files/construct_num.txt\n");
	printf("\ts : construct the skiplist with data read from file test_files/construct_num.txt and search elements from file test_files/search_num..txt\n\t\tPrint statistics about the searches.\n");
	printf("\ti : construct the skiplist with data read from file test_files/construct_num.txt and search, using an iterator, elements read from file test_files/search_num.txt\n\t\tPrint statistics about the searches.\n");
	printf("\tr : construct the skiplist with data read from file test_files/construct_num.txt, remove values read from file test_files/remove_num.txt and print the list in reverse order\n");
	printf("where num is the file number for input\n");
}

void test_construction(int num){
	FILE *fic;
	char *fichier;
	
	switch (num){
		case 1:
			sprintf(fichier,"test_files/construct_1.txt",num);
			break;
		case 2:
			sprintf(fichier,"test_files/construct_2.txt",num);
			break;
		case 3:
			sprintf(fichier,"test_files/construct_3.txt",num);
			break;
		case 4:
			sprintf(fichier,"test_files/construct_4.txt",num);
			break;
		default:
			break;
	}

	fic=fopen(fichier,"r");
  	if (fic==NULL){
  		fprintf(stderr,"\n Erreur Fichier : Impossible de lire le fichier %s\n",fichier);
    	exit(-1);
    }
   
	
	int node, level, value;
	fscanf(fic, "%d", &level); 
	fscanf(fic, "%d", &node);
	SkipList d;
	d = skiplist_create(level); 
	for(i = O;i < node;i++){
		fscanf(fic, "%d", &value);
		skiplist_insert(d, value);
	}
	printf("Skiplist size = %d\n",skiplist_size(d));

	for(unsigned int i = 0;i < skiplist_size(d);i++){
		printf("%d ", skiplist_ith(d, i));
		i++;
	}
	skiplist_delete(d);
	fclose(fic); 
}

void test_search(int num){
	(void) num;
}

void test_search_iterator(int num){
	(void) num;
}

void test_remove(int num){
	(void) num;
}

void generate(int nbvalues);


int main(int argc, const char *argv[]){
	if (argc < 3) {
		usage(argv[0]);
		return 1;
	}
	switch (argv[1][1]) {
		case 'c' :
			test_construction(atoi(argv[2]));
			break;
		case 's' :
			test_search(atoi(argv[2]));
			break;
		case 'i' :
			test_search_iterator(atoi(argv[2]));
			break;
		case 'r' :
			test_remove(atoi(argv[2]));
			break;
		case 'g' :
			generate(atoi(argv[2]));
			break;
		default :
			usage(argv[0]);
			return 1;
	}
	return 0;
}



void generate(int nbvalues){
	FILE *output;
	int depth;
	int maxvalue;
	output = fopen("construct.txt", "w");
	srand(nbvalues);
	depth = rand()%16;
	maxvalue = rand()%10 * nbvalues;
	fprintf(output, "%d\n%d\n", depth, nbvalues);
	for (int i=0; i< nbvalues; ++i) {
		fprintf(output, "%d\n", rand()%maxvalue);
	}
	fclose(output);
	output = fopen("search.txt", "w");
	srand(rand());
	nbvalues *= depth/4;
	fprintf(output, "%d\n", nbvalues);
	for (int i=0; i< nbvalues; ++i) {
		fprintf(output, "%d\n", rand()%maxvalue);
	}
	fclose(output);
}


