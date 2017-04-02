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
	char file[27];
	
	sprintf(file,"test_files/construct_%d.txt",num);

  	if ((fic = fopen(file,"r")) == NULL){
  		fprintf(stderr,"\n Erreur Fichier : Impossible de lire le fichier %s\n",file);
    	exit(-1);
    }
   
	
	int level, value;
	unsigned int node;
	fscanf(fic, "%d", &level); 
	fscanf(fic, "%u", &node);
	SkipList d;
	d = skiplist_create(level); 

	/* Insert all values in file */
	for(unsigned int i = 0;i < node;i++){
		fscanf(fic, "%d", &value);
		d = skiplist_insert(d, value);
	}

	node = skiplist_size(d);
	printf("Skiplist (%u)\n",node);

	/* Access all the values of the list */
	for(unsigned int i = 0;i < skiplist_size(d);i++){
		printf("%d ", skiplist_ith(d, i));
	}

	printf("\n");
	skiplist_delete(d);
	fclose(fic); 
}

void test_search(int num){
	SkipList d; 
	FILE *fic;
	char file[27];
	unsigned int nb_node;
	int nb_level;
	int value;
	unsigned int n;
	unsigned int min;
	unsigned int max;
	unsigned int sum;
	unsigned int nb_operations;
	unsigned int nb_found;
    
	sprintf(file,"test_files/construct_%d.txt",num);

	if ((fic = fopen(file,"r")) == NULL){
    	fprintf(stderr,"\n Erreur Fichier : Impossible de lire le fichier %s\n",file);
    	exit(1);  
    }
   
   
	fscanf(fic, "%d", &nb_level);
	fscanf(fic, "%u", &nb_node);
	d = skiplist_create(nb_level);

	/* Insert all values in file */
	for(unsigned int i = 0;i<nb_node;i++) {
    	fscanf(fic, "%d", &value);
    	d = skiplist_insert(d,value);
	}
	fclose(fic); 
  
	nb_node = skiplist_size(d);
  
	sprintf(file, "test_files/search_%d.txt", num);
  
	if ((fic = fopen(file,"r")) == NULL){
		fprintf(stderr, "\n Erreur Fichier : Impossible de lire le fichier %s\n", file);
 	   exit(1); 
	}
	fscanf(fic, "%u", &n);
	nb_found = 0;
	min = n;
	max = 0;
	sum = 0;
	
	/* Search for every elems of the file */
	for(unsigned int i=0;i<n;i++){
		fscanf(fic, "%d", &value);
		if(skiplist_search(d, value, &nb_operations)){
			printf("%d -> true\n",value);
			nb_found++;
		}
    	else
			printf("%d -> false\n",value);
    
		sum = sum + nb_operations;
		if(min > nb_operations)
			min = nb_operations;
    
		if(max < nb_operations)
			max = nb_operations;
	}
  
	printf("Statistics :\n");
	printf("    Size of the list : %u\n", nb_node);
	printf("Search %d values :\n", n);
	printf("    Found %d\n", nb_found);
	printf("    Not found %d\n", n - nb_found);
	printf("    Min number of operations : %d\n", min);
	printf("    Max number of operations : %d\n", max);
	printf("    Mean number of operations : %d\n", sum / n);
    
	fclose(fic);
	skiplist_delete(d); 
}

void test_search_iterator(int num){
	SkipList d; 
	FILE *fic;
	char file[27];
	unsigned int node;
	int nb_level;
	int value;
	unsigned int n;
	unsigned int min;
	unsigned int max;
	unsigned int sum;
	unsigned int nb_operations;
	unsigned int nb_found;
	bool found;
    
	sprintf(file,"test_files/construct_%d.txt",num);
  
	if ((fic=fopen(file,"r"))==NULL){
		fprintf(stderr,"\n Erreur Fichier : Impossible de lire le fichier %s\n",file);
		exit(1); 
	}
   
	fscanf(fic,"%d",&nb_level);
   	fscanf(fic,"%u",&node);
	d=skiplist_create(nb_level);

	/* Insert all values in file */
	for(unsigned int i=0;i<node;i++) {
		fscanf(fic,"%d",&value);
		d=skiplist_insert(d,value);
	}
	fclose(fic); 
  
	node = skiplist_size(d);
	sprintf(file,"test_files/search_%d.txt",num);

	if ((fic = fopen(file,"r"))==NULL){
		fprintf(stderr,"\n Erreur Fichier : Impossible de lire le fichier %s\n",file);
		exit(1); 
	}
	fscanf(fic,"%u",&n);
  
	SkipListIterator it = skiplist_iterator_create(d,FORWARD_ITERATOR);
	nb_found = 0;
	min = n;
	max = 0;
	sum = 0;

	/* Search for every values in the file */
	for(unsigned int i=0;i<n;i++){
		fscanf(fic,"%d",&value);
		nb_operations = 0;
		found = false;

		/* Use iterator to go through the list */
		for(it = skiplist_iterator_begin(it); !skiplist_iterator_end(it);it = skiplist_iterator_next(it)){
			nb_operations++;
      
			if(skiplist_iterator_value(it) == value){
				printf("%d -> true\n",value);
				found = true;
				nb_found++;
				break;
			}
		}
    
    	if(!found)
			printf("%d -> false\n",value);
    
   		if(min > nb_operations)
			min = nb_operations;
    
    	if(max < nb_operations)
			max = nb_operations;
    
    	sum = sum + nb_operations;
	}
  
	skiplist_iterator_delete(it);
  
	printf("Statistics :\n");
	printf("    Size of the list : %u\n", node);
  
	printf("Search %d values :\n", n);
	printf("    Found %d\n", nb_found);
	printf("    Not found %d\n", n-nb_found);
	printf("    Min number of operations : %d\n", min);
	printf("    Max number of operations : %d\n", max);
	printf("    Mean number of operations : %d\n", sum/n);
    
	fclose(fic);
	skiplist_delete(d);
}

void test_remove(int num){	 
	SkipList d; 
	FILE *fic;
	char file[27];
	unsigned int n;
	unsigned int node;
	int nb_level;
	int value;
   
	sprintf(file,"test_files/construct_%d.txt",num);
	if ((fic = fopen(file,"r")) == NULL){
		fprintf(stderr,"\n Erreur Fichier : Impossible de lire le fichier %s\n",file);
		exit(1);
      
	}
   
	fscanf(fic,"%d",&nb_level);
   	fscanf(fic,"%u",&node);
	d = skiplist_create(nb_level);

	/* Insert all values in file */
	for(unsigned int i = 0;i<node;i++) {
		fscanf(fic,"%d",&value);
		d = skiplist_insert(d,value);
	}
	fclose(fic);
  
	sprintf(file,"test_files/remove_%d.txt",num);
	if ((fic = fopen(file,"r")) == NULL){
		fprintf(stderr,"\n Erreur Fichier : Impossible de lire le fichier %s\n",file);
		exit(1); 
	}
	fscanf(fic,"%u",&n);

	/* Remove all the values in file */
	for(unsigned int i=0;i<n;i++){
		fscanf(fic,"%d", &value);
		d = skiplist_remove(d,value);
	}
	printf("Skiplist (%u)\n",skiplist_size(d));
  
	for(unsigned int i = skiplist_size(d);i>0;--i)
		printf("%d ",skiplist_ith(d,i-1)); 
  
	printf("\n");
	fclose(fic);
	skiplist_delete(d);
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


