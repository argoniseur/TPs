#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#ifndef __RBTREE__
#define __RBTREE__



/* -------------------------------------------- */
/*    Type definition :                            */
/* -------------------------------------------- */

typedef struct _rbtree *RedBlackTree;

void rbtree_export_dot(RedBlackTree t, FILE *file);

RedBlackTree rbtree_create();

RedBlackTree rbtree_construct(RedBlackTree left,RedBlackTree right, int root);

bool rbtree_empty(RedBlackTree t);

RedBlackTree rbtree_left(RedBlackTree t);

RedBlackTree rbtree_right(RedBlackTree t);

void leftrotate(RedBlackTree *x);

void rightrotate(RedBlackTree *y);

void rbtree_add(RedBlackTree *t, int v);

RedBlackTree grandparent(RedBlackTree x);

RedBlackTree uncle(RedBlackTree x);

void fix_insert_case0(RedBlackTree *x);

void fix_insert_case1(RedBlackTree *x);

void fix_insert_case2(RedBlackTree *x);

void fixredblackproperties_insert(RedBlackTree *x);

void fix_insert_case2_right(RedBlackTree *x);

void fix_insert_case2_left(RedBlackTree *x);

#endif
