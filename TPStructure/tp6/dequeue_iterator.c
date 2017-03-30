#include "dqueue.h"

DqueueIterator deque_iterator_create(Deque l){
    DqueueIterator it = (DqueueIterator)malloc(sizeof(struct s_dqueue_iterator));
    it->l = l;
    it->begin = l->sentinel->next;
    it->current = it->begin;
    return(it);
}

bool hasNext (DqueueIterator i){
    return (i->current->next != NULL);
}

bool hasPrevious (DqueueIterator i){
    return (i->current->previous != NULL);
}

Cellule next(DqueueIterator i){
    if (!hasNext(i))
        return NULL;
    
    i->current = i->current->next;
    return i->current->previous;
}

Cellule previous(DqueueIterator i){
    if (!hasPrevious(i))
        return NULL;
    
    i->current = i->current->previous;
    return i->current->next;
}

DqueueIterator begin(DqueueIterator i){
    i->current = i->begin;
    return i;
}

DqueueIterator end(DqueueIterator i){
    i->current = i->begin->previous;
    return i;
}

void map(Deque l, void(*process)(unsigned int *, void*), void *user_data){
    
    Cellule courant = l->sentinel->next;
    for(int i=0;i<l->size;i++){
        (*process) (&(courant->elem->valeur), user_data);
        courant = courant->next;
    }
}
