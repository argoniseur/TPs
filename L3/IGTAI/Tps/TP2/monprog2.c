#include "limace.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc,const char* argv[]){
	if (argc != 3){
		exit (1);
	}
	Image gI;
	gI = ImRead(argv[1]);
	if (gI == NULL){
		exit(2);
	}
	int nbR = ImNbRow(gI);
	int nbC = ImNbCol(gI);
	unsigned char ** I = ImGetI(gI);
	Matrix mat = MatCAlloc(Int,256,1);
	int ** hist = MatGetInt(mat);
	for (int r = 0; r<nbR; r++)
		for(int c = 0; c<nbC; c++)
			hist[0][I[r][c]]++;
	for (int i = 1; i<256; i++){
		hist[i][0] = hist[i-1][0]+hist[i][0];
	}
	MatWriteAsc(mat,argv[2]);
	MatFree(&mat);
	ImFree(&gI);
}
