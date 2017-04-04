#ifndef _QUEUE_H__
#define _QUEUE_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define TMAX 5
typedef struct Queue_s
{
	int tab[TMAX];
	int head;
	int tail;
	int nb_elem;
} Queue;

void init_Queue(Queue *q);
bool empty_Queue (Queue q);
bool full_Queue (Queue q);
void affiche_Queue (Queue q);
void push (Queue *q, int e);
void pop (Queue *q);
int nb_elem(Queue *q);
#endif
