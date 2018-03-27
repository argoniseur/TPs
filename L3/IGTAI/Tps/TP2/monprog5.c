#include "limace.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc,const char* argv[]){
	if (argc != 4){
		exit (1);
	}
	Matrix mIni;
	mIni = MatReadAsc(argv[1]);
	if (mIni == NULL){
		exit(2);
	}
	Matrix mD;
	mD = MatReadAsc(argv[2]);
	if (mD == NULL){
		exit(2);
	}
	Matrix mat = MatCAlloc(Int,256,1);
	int ** histD = MatGetInt(mD);
	int ** hist = MatGetInt(mIni);
	int ** histF = MatGetInt(mat);
	for(int c = 0; c<256; c++){
		int i = 0;
		for (;hist[c][0]>histD[i][0]&&255>i;i++);
		if(i == 0){
			histF[c][0]=i;
		}else{
			if (histD[c][0]-hist[i][0]<hist[c][0]-histD[i-1][0]){
				histF[c][0] = i;
			}else{
				histF[c][0] = i-1;
			}
		}
	}
		
	
	MatWriteAsc(mat,argv[3]);
	MatFree(&mat);
	MatFree(&mIni);
	MatFree(&mD);
}
