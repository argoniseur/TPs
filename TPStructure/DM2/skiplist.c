#include <stdlib.h>
#include <assert.h>

#include "rng.h"
#include "skiplist.h"
#define NB_LEVEL 4

typedef struct s_node{
	int value;
	int node_level;
	struct s_node *tabPrecedent[NB_LEVEL];
	struct s_node *tabSuivant[NB_LEVEL];
}*Node;

struct s_SkipList{
	Node head[NB_LEVEL];
};

SkipList skiplist_create(int nblevels){
	SkipList s = (SkipList)malloc(sizeof(struct s_SkipList));
	for (int i = 0;i<nblevels;i++)
		s->head[i] = NULL;
	return s;
}

void skiplist_delete(SkipList d){
	Node elem;
	while (d->head[0] != NULL){
		elem = d->head[0];
		d->head[0] = d->head[0]->tabSuivant[0];
		free(elem);
	}
}