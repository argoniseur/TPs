#include "limace.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Image Hist2Im(Matrix Hist, int NbLig)
{
    unsigned char **I;
    int *h,i,j,Max=0,NbCol=256;
    Image Resultat;
    
    if (MatType(Hist)!=Int) return NULL;
    Resultat=ImCAlloc(GrayLevel,NbLig,NbCol);
    h=*MatGetInt(Hist);
    for (j=0;j<NbCol;j++)
        if (h[j]>Max) Max=h[j];
    I=ImGetI(Resultat);
    for (j=0;j<256;j++)
        for (i=NbLig-1;i>=(NbLig-NbLig*h[j]/Max);i--)
            I[i][j]=255;
    return Resultat;    
}

int main (int argc,const char* argv[]){
	if ( argc !=3){
		exit (1);
	}
	Image gI;
	gI = ImRead(argv[1]);
	if (gI == NULL){
		exit(2);
	}
	int nbR = ImNbRow(gI);
	int nbC = ImNbCol(gI);
	Matrix mat = MatCAlloc(Int,256,1);
	int ** hist = MatGetInt(mat);
	int x = (nbR*nbC)/256;
	hist[0][0] = x;
	for (int i = 1; i<256; i++)
		hist[i][0] = hist[i-1][0]+x;
	MatWriteAsc(mat,argv[2]);
	ImWrite(Hist2Im(mat,256), "sortie.pgm");
	MatFree(&mat);
	ImFree(&gI);
}
