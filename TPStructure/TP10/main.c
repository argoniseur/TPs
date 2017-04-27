#include "rbtree.h"

int main(void){
	RedBlackTree tree = rbtree_create();
	for (int i=0;i<10;i++)
		rbtree_add(&tree,i);
	//rbtree_add(&tree,4);
	//rbtree_add(&tree,6);
	//rbtree_add(&tree,5);
	//rbtree_add(&tree,7);
	//rbtree_add(&tree,2);
	//rbtree_add(&tree,3);
	//rbtree_add(&tree,1);
	
	
	//rbtree_add(&tree,7);
	//rbtree_add(&tree,9);
	//rbtree_add(&tree,5);
	//rbtree_add(&tree,4);
	
	FILE* fic = fopen("fichier.dot","w");
	rbtree_export_dot(tree,fic);
	return 0;
}
