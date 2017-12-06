#include "rbtree.h"


/* -------------------------------------------- */
/*    Private interface :                            */
/*    binary search tree with red-black coloring    */
/* -------------------------------------------- */


/* -------------------------------------------- */
/*    Type definition :                            */
/* -------------------------------------------- */

#define RED 'r'
#define BLACK 'b'

struct _rbtree {
    RedBlackTree parent;
    RedBlackTree left;
    RedBlackTree right;
    int root;
    unsigned char color;
};
 

/* -------------------------------------------- */
/*    Visitors                                    */
/* -------------------------------------------- */

#define MAXFILE 4096
typedef struct s_queue {
    RedBlackTree queue[MAXFILE];
    int head;
    int tail;
} *QueueOfBinaryTrees;

QueueOfBinaryTrees queue_create() {
    QueueOfBinaryTrees f = (QueueOfBinaryTrees) malloc(sizeof(struct s_queue));
    f->head = 0;
    f->tail = 0;
    return f;
}

void queue_push(QueueOfBinaryTrees f, RedBlackTree a) {
    f->queue[f->head] = a;
    f->head = (f->head + 1) % MAXFILE;
}

RedBlackTree queue_pop(QueueOfBinaryTrees f) {
    RedBlackTree a = f->queue[f->tail];
    f->tail = (f->tail + 1) % MAXFILE;
    return (a);
}

int queue_empty(QueueOfBinaryTrees f) {
    return (f->tail == f->head);
}

void queue_delete(QueueOfBinaryTrees f) {
    free(f);
}



/* -------------------------------------------- */
/*    Export the tree as a dot file                */
/* -------------------------------------------- */

void printNode(RedBlackTree n, FILE *file){
    
    if (n->color == RED) {
        
        fprintf(file, "\tn%d [style=filled, fillcolor=red, label=\"{{<parent>}|%d|{<left>|<right>}}\"];\n",
                n->root, n->root);
    } else {
        fprintf(file, "\tn%d [style=filled, fillcolor=grey, label=\"{{<parent>}|%d|{<left>|<right>}}\"];\n",
                n->root, n->root);
    }
    
    if (n->left){
        fprintf(file, "\tn%d:left:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                n->root, n->left->root);
    } else {
        fprintf(file, "\tlnil%d [style=filled, fillcolor=black, label=\"NIL\"];\n", n->root);
        fprintf(file, "\tn%d:left:c -> lnil%d:c [headclip=false, tailclip=false]\n",
                n->root, n->root);
    }
    if (n->right){
        fprintf(file, "\tn%d:right:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                n->root, n->right->root);
    } else {
        fprintf(file, "\trnil%d [style=filled, fillcolor=black, label=\"NIL\"];\n", n->root);
        fprintf(file, "\tn%d:right:c -> rnil%d:c [headclip=false, tailclip=false]\n",
                n->root, n->root);
    }
    
}

void rbtree_export_dot(RedBlackTree t, FILE *file) {
    QueueOfBinaryTrees q = queue_create();
    fprintf(file, "digraph RedBlackTree {\n\tgraph [ranksep=0.5];\n\tnode [shape = record];\n\n");
    
    queue_push(q, t);
    while (!queue_empty(q)) {
        t = queue_pop(q);
        printNode(t, file);
        if (!rbtree_empty(rbtree_left(t)))
            queue_push(q, rbtree_left(t));
        if (!rbtree_empty(rbtree_right(t)))
            queue_push(q, rbtree_right(t));
    }
    
    fprintf(file, "\n}\n");
}


/*---------------------------------------------------*/
/*      Implementation of RedBlackTree              */
/*---------------------------------------------------*/

RedBlackTree rbtree_create(){
    return NULL;
}

RedBlackTree rbtree_construct(RedBlackTree left,RedBlackTree right, int root){
  
  RedBlackTree t = (RedBlackTree)malloc(sizeof(struct _rbtree));
  
  //initialisation de t qui devient la racine de l'arbre
  t->parent = NULL;
  t->left = left;
  t->right = right;
  t->root = root;
  
  //initialisation du parent de l'arbre de gauche
  if(left)
    left->parent = t;
  
  //initialisation du parent de l'arbre de droite
  if(right)
    right->parent = t;
  
  return t;
  
}

bool rbtree_empty(RedBlackTree t){
	return (t == NULL);
}

RedBlackTree rbtree_left(RedBlackTree t){
	return t->left;
}

RedBlackTree rbtree_right(RedBlackTree t){
	return t->right;
}

void leftrotate(RedBlackTree *t){
    
    RedBlackTree x = *t;
    RedBlackTree y = x->right;
    x->right = y->left;
    
    if(y->left != NULL)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if(y->parent!=NULL){
        if(x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
    *t = y;
}

void rightrotate(RedBlackTree *t){
    
		RedBlackTree y = *t;
        RedBlackTree x = y->left;
        y->left = x->right;
        
        if (x->right != NULL)
			x->right->parent = y;
        x->parent = y->parent;
        
        if (x->parent != NULL) {
                if (y == y->parent->right)
					y->parent->right = x;
                else
					y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
        *t = x;
}



void rbtree_add(RedBlackTree *t,int root) {
	RedBlackTree new=rbtree_construct(NULL,NULL,root);
		new->color=RED;
	RedBlackTree itr=*t;
	RedBlackTree tmpNode;
	if(itr){
		do{
			tmpNode=itr;
			if(root > itr->root){
				itr=itr->right;
				if(!itr){
					tmpNode->right=new;
					new->parent=tmpNode;
				}
			}
			else{
				itr=itr->left;
				if(!itr){
					tmpNode->left=new;
					new->parent=tmpNode;
				}
			}
		}while(itr);
	}
	else
		*t=new;
	fixredblackproperties_insert(&new);
}

RedBlackTree grandparent(RedBlackTree x){
    
    if((x != NULL) && (x->parent != NULL))
        return x->parent->parent;
    else
        return NULL;
}

RedBlackTree uncle(RedBlackTree x){
    RedBlackTree y = grandparent(x);
    
    if(y == NULL)
        return NULL;
    if(x->parent == y->left)
        return y->right;
    else
        return y->left;
}

void fixredblackproperties_insert(RedBlackTree *x){
    if ((*x)->color == RED)
        fix_insert_case0(x);
}

void fix_insert_case0(RedBlackTree *x){
        if((*x)->parent == NULL)
			(*x)->color = BLACK;
        else if ((*x)->parent->color == RED)
			fix_insert_case1(x);

}

void fix_insert_case1(RedBlackTree *x){
        RedBlackTree f = uncle((*x));
		if(f != NULL && f->color == RED){
			RedBlackTree pp = grandparent((*x));
            (*x)->parent->color = BLACK;
            f->color = BLACK;
            pp->color = RED;
            fix_insert_case0(&pp);
		}
		else
			fix_insert_case2(x);
}

void fix_insert_case2(RedBlackTree *x) {
        if (grandparent((*x)) == (*x)->parent) {
                fix_insert_case2_left(x);
        } else{
                fix_insert_case2_right(x);
        }
}

void fix_insert_case2_left(RedBlackTree *x) {
        RedBlackTree p =  ((*x)->parent);
        RedBlackTree pp = grandparent((*x));
        if ((*x) == (p)->right) {
                leftrotate(&p);
                (*x) = ((*x)->left);
        }
        (*x)->parent->color = BLACK;
        (pp)->color = RED;
        rightrotate(&pp);
}

void fix_insert_case2_right(RedBlackTree *x) {
        RedBlackTree p = ((*x)->parent);
        RedBlackTree pp = grandparent((*x));
        if ((*x) == (p)->right) {
                rightrotate(&p);
                (*x) = ((*x)->left);
        }
        (*x)->parent->color = BLACK;
        (pp)->color = RED;
        leftrotate(&pp);
}
