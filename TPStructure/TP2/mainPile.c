#include <stdlib.h>
#include <stdio.h>
#include "Pile.h"


int main(void){
	Stack pile;
	
	pile = stack();
	for(int i=0;i<10;i++){
		pile = push(pile,i);
	}
	draw_stack(pile);
	delete_pile(pile);
	
	return 0;
}
