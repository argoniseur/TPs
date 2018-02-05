
#include "Pile.h"
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#define STACK_SIZE 16

typedef struct s_element{
    int value;
    struct s_element *next;
}*Element;

struct s_stack{
	Element top;
};

Stack stack(void){
	Stack s;
	s=(Stack)malloc(sizeof(struct s_stack));
	s->top=NULL;
	return(s);
}

Stack push(Stack s, int e){
	Element new = (Element)malloc(sizeof(struct s_element));
	new->value = e;
	new->next = s->top;
	s->top=new;
	return(s);
}

int top(Stack s){
	return (s->top->value);
}
	
bool empty(Stack s){
	return(s->top == NULL);
}

Stack pop(Stack s){
	assert(!empty(s));
	Element e = s->top;
	s->top = e->next;
	free(e);
	return(s);
}

void draw_stack(Stack s){
	Element new;
	new = s->top;
	do{
		printf("%d\n", new->value);
	}while((new = new->next) != NULL);
}

void delete_pile(Stack s){
	do{
		s = pop(s);
	}while(s->top->next != NULL);
	free(s->top);
	free(s);
}
