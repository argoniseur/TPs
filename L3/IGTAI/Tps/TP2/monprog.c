#include "limace.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main (int argc,const char* argv[]){
	if (argc != 4){
		fprintf(stderr,"Usage %s fIn fOut Mat-LUT\n",argv[0]);
		exit (1);
	}
	Image gImage = ImRead(argv[1]);
	int nbC = ImNbCol(gImage);
	int nbR = ImNbRow(gImage);
	unsigned char **I = ImGetI(gImage);
	Matrix lut = MatReadAsc(argv[3]);
	int **mat = MatGetInt(lut);
	Image res = ImCAlloc(GrayLevel,nbR,nbC);
	unsigned char **Ires = ImGetI(res);
	for (int i = 0; i<nbR; i++){
		for (int j = 0; j<nbC; j++){
				Ires[i][j] = mat[I[i][j]][0];
		}
	}
	ImWrite(res,argv[2]);
	MatFree(&lut);
	ImFree(&gImage);
	ImFree(&res);
}
