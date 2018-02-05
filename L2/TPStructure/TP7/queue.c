#include "queue.h"


void init_Queue(Queue *q){
	q->head=0;
	q->tail=0;
	q->nb_elem=0;
}

bool empty_Queue (Queue q){
	return (q.nb_elem==0);
}

bool full_Queue (Queue q){
	return (q.nb_elem == TMAX);
}

void affiche_Queue (Queue q){
	for (int i = q.head;i<=q.nb_elem;i++){
		printf("%d ",q.tab[i]);
	}
}


void push (Queue *q, int e){
	if (!full_Queue(*q)){
		q->nb_elem++;
		q->tab[q->tail++]=e;
	}
	else 
		printf("Il n'y a plus de place\n");
}


void pop (Queue *q){
	if (empty_Queue(*q)){
		printf("Erreur, la pile est vide\n");
		return;
	}
	else{
		q->nb_elem--;
		q->head++;
	}
}

int nb_elem(Queue *q){
	return q->nb_elem;
}

void vider_queue(FILE *f_in, Queue *q){
  while (!empty_Queue(*q)) {
    fprintf(f_in, "%d ", q->tab[q->head]);
    pop(q);
  }
}
