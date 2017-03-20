#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

#ifndef STRUCTUREDONNEES_PILE_H
#define STRUCTUREDONNEES_PILE_H

typedef struct s_stack *Stack;

Stack stack(void);

Stack push(Stack s, int e);

bool empty(Stack s);

Stack pop(Stack s);

int top(Stack s);

void draw_stack(Stack s);

void delete_pile(Stack s);

#endif //STRUCTUREDONNEES_PILE_H
