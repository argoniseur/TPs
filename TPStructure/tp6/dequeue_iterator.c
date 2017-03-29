#include "dqueue.h"

struct s_dqueue_iterator{
    Dqueue l;
    Node current;
    Node (*next) (Node);
    Node begin;
};

bool hasNext (DqueueIterator i){
    return (i->current->suivant != NULL);
}

bool hasPrevious (DqueueIterator i){
    return (i->current->precedent != NULL);
}

Node next(DqueueIterator i){
    if (!hasNext(i))
        return NULL;
    
    i->current = i->current->suivant;
    return i->current->precedent;
}

Node previous(DqueueIterator i){
    if (!hasPrevious(i))
        return NULL;
    
    i->current = i->current->precedent;
    return i->current->suivant;
}

DqueueIterator begin(DqueueIterator i){
    i->current = i->begin->suivant;
    return i;
}

DqueueIterator end(DqueueIterator i){
    i->current = i->begin->precedent;
    return i;
}
