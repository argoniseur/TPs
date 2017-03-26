#include <stdlib.h>
#include <assert.h>

#include "rng.h"
#include "skiplist.h"
#define NB_LEVEL_MAX 4

/** Node struct, this is the type of our list's cells */
typedef struct s_node{
	int value;
	int node_level;
	struct s_node **previous;
	struct s_node **next;
}*Node;

/** SkipList, explicit enough */
struct s_SkipList{
	int level_max;
	unsigned int size;
	Node sentinel;
	RNG seed;
};


SkipList skiplist_create(int nblevels){

	/** Allows memory, set levels, size and seed */
	SkipList s = (SkipList)malloc(sizeof(struct s_SkipList));
	s->level_max = nblevels;
	s->size = 0;
	s->seed = rng_initialize(0);

	/** Initialize sentinel properly. Value is set to -1 and node_level to level_max */
	s->sentinel = (Node)malloc(sizeof(struct s_node));
	s->sentinel->next = (Node*)malloc(nblevels*sizeof(struct s_node));
	s->sentinel->previous = (Node*)malloc(nblevels*sizeof(struct s_node));
	s->sentinel->value = -1;
	s->sentinel->node_level = nblevels;

	/** Makes the sentinel point itself */
	for (int i=0;i<nblevels;i++){
		s->sentinel->next[i] = s->sentinel;
		s->sentinel->previous[i] = s->sentinel;
	}
	return s;
}

void skiplist_delete(SkipList d){
	Node elem = d->sentinel->next[0];
	Node temp;

	/** Clean every elements in the list */
	while (elem != d->sentinel){
		temp = elem;
		free(elem->next);
		free(elem->previous);
		free(elem);
		elem = temp->next[0];
	}

	/** Clean sentinel */
	free(d->sentinel->next);
	free(d->sentinel->previous);
	free(d->sentinel);
	free(d);
}

unsigned int skiplist_size(SkipList d){
	return d->size;
}

int skiplist_ith(SkipList d, unsigned int i){
	unsigned int n = 0;
	Node elem = d->sentinel->next[0];

	/** Va à l'index désigné par i et en renvoie la valeur */
	while (i != n){
		n++;
		elem = elem->next[0];
	}
	return elem->value;
}

bool skiplist_search(SkipList d, int value, unsigned int *nb_operations){
  Node parcours = d->sentinel;
  *nb_operations=1;

  for(int i = (d->level_max)-1;i >= 0; --i){
    while(value > parcours->next[i]->value){
      parcours = parcours->next[i];
      *nb_operations++;
    }
    
    if((parcours->next[i]->value == value) && (parcours->next[i] != d->sentinel))
      return true;
  }
  
  return false;
}

