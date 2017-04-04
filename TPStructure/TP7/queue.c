#include "queue.h"


void init_Queue(Queue *q)
{
//voir pour le tail
	q->head=0;
	q->tail=0;
	q->nb_elem=0;
}

bool empty_Queue (Queue q)
{
	return (q.nb_elem==0);
}

bool full_Queue (Queue q)
{
	return (q.nb_elem==TMAX);
}

void affiche_Queue (Queue q)
{
	int i;
	for (i=q.head;i<=q.nb_elem;i++)
	{
		printf("%d ",q.tab[i]);
	}
}


void push (Queue *q, int e)
{
	if (!full_Queue(*q))
	{
		//faire attention au signe du modulo, des fois il est négatif
		q->nb_elem++;
		//q->tail=(q->tail%TMAX)++;
		q->tab[q->tail++]=e;
		//a++ POST INCRÉMENTATION
		//++a PRÉ INCRÉMENTATION
	}
	else 
		printf("Il n'y a plus de place\n");
}


void pop (Queue *q)
{
	if (empty_Queue(*q))
	{
		printf("Erreur, la pile est vide\n");
		return;
	}
	else
	{
		q->nb_elem--;
		q->head++;
	}
}

int nb_elem(Queue *q) {	return q->nb_elem; }