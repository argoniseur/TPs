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

SkipList skiplist_insert(SkipList d, int value){
  
	Node e[d->level_max];
	d->sentinel->value = value;
	Node current = d->sentinel;
  
  	for(int i = d->level_max-1;i>=0;--i){
		while(value>current->next[i]->value)
			current = current->next[i];
		e[i] = current->next[i];
	}
	current = current->next[0];
  

	if(current != d->sentinel && current->value == value)
		return d;
  
	int niveau;
  	niveau = rng_get_value(&(d->seed),(d->level_max)-1);
 	current = (Node)malloc(sizeof(struct s_node));
	current->next = (Node*)malloc(niveau*sizeof(struct s_node));
	current->previous = (Node*)malloc(niveau*sizeof(struct s_node));
	current->value = value;
	current->node_level = niveau+1;
  
	for(int i = 0;i<=niveau;++i){
		current->next[i] = e[i];
		current->previous[i] = e[i]->previous[i];
		current->next[i]->previous[i] = current;
		current->previous[i]->next[i] = current;
	}
	(d->size)++;
  
	return d;   
}

void skiplist_map(SkipList d, ScanOperator f, void *user_data){
  Node current = d->sentinel->next[0];
  
  for(unsigned int i = 0;i<d->size;i++){
    f(current->value,user_data);
    current = current->next[0];
  }
}

bool skiplist_search(SkipList d, int value, unsigned int *nb_operations){
  Node parcours = d->sentinel;
  *nb_operations = 1;

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

  
struct s_SkipListIterator{
  SkipList d;
  Node begin;
  Node current;
  Node (*next)(Node);
};

Node next(Node e){
	return e->next[0];
}

Node previous(Node e){
	return e->previous[0]; 
}

SkipListIterator skiplist_iterator_create(SkipList d, unsigned char w){
	SkipListIterator it = (SkipListIterator)malloc(sizeof(struct s_SkipListIterator));
	it->d = d;
  
	if(w == FORWARD_ITERATOR){
		it->begin = d->sentinel->next[0];
		it->next = next;
    }
	else{ 
		it->begin=d->sentinel->previous[0];
		it->next = previous;
    
	}
  	it->current = it->begin;
  
	return it;
}

void skiplist_iterator_delete(SkipListIterator it){
	free(it);
}

SkipListIterator skiplist_iterator_begin(SkipListIterator it){
	it->current = it->begin;
	return it; 
}

bool skiplist_iterator_end(SkipListIterator it){
	return (it->current == it->d->sentinel);
}

SkipListIterator skiplist_iterator_next(SkipListIterator it){
	it->current = it->next(it->current);
	return it;
}

int skiplist_iterator_value(SkipListIterator it){
  return it->current->value;
}

SkipList skiplist_remove(SkipList d, int value){
	d->sentinel->value = value;
	Node courant = d->sentinel;
  
	for (int i = d->level_max-1; i >=0; --i) {
		while (value > courant->next[i]->value)
			courant = courant->next[i];
	}
	courant=courant->next[0];	

	if (courant != d->sentinel && courant->value == value) {
		for (int i=0; i<courant->node_level; ++i) {
			courant->previous[i]->next[i] = courant->next[i];
			courant->next[i]->previous[i] = courant->previous[i];
		}
   		d->size--;
		free(courant->previous);
		free(courant->next);
		free(courant);
    }
  
  return d;
}