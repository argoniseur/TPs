#include <stdio.h>
#include <stdlib.h>
#include "limace.h"
#include <math.h>





int main(int argc, char ** argv){
	/* Exercice 1 */
	if (argc != 2)
		exit(99);
		
	Image imgLue = ImRead(argv[1]);
	int row, col;
	row = ImNbRow(imgLue);
	col = ImNbCol(imgLue);
	Image imgGris = ImAlloc(GrayLevel,row,col);
	
	int i, j;
	unsigned char **matI, **R, **G, **B;
	matI = ImGetI(imgGris);
	R = ImGetR(imgLue);
	G = ImGetG(imgLue);
	B = ImGetB(imgLue);
	
	for (i = 0; i<row; i++)
		for (j = 0; j<col; j++)
			matI[i][j] = round(0.299*R[i][j] + 0.587*G[i][j] + 0.114*B[i][j]);
	
	ImWrite(imgGris, "lol.pgm");
	ImFree(&imgLue);
	
	
	/* Exercice 2 */
	imgLue = ImRead("lol.pgm");
	row = ImNbRow(imgLue);
	col = ImNbCol(imgLue);
	matI = ImGetI(imgLue);
	
	Matrix histo = MatAlloc(Int, 1, 256);
	int **M = MatGetInt(histo);
	int GrayLvl;
	
	for (i = 0; i<row; i++)
		M[0][i] = 0;
		
	for (i = 0; i<row; i++)
		for (j = 0; j<col; j++){
			GrayLvl = matI[i][j];
			M[0][GrayLvl] += 1;
		}
	
	//valeur max de l'histo
	int maxVal = 0;
	for (i = 0; i<256; i++)
		if (maxVal < M[0][i]) {maxVal = M[0][i];}
	maxVal += 10;
	
	//Création de l'image blanche
	Image imgHist = ImAlloc(GrayLevel,maxVal,256);
	matI = ImGetI(imgHist);
	row = ImNbRow(imgHist);
	col = ImNbCol(imgHist);
	
	for (i = 0; i<row; i++)
		for (j = 0; j<col; j++)
			matI[i][j] = 255;
	
	// Remplissage des pixels
	for (i = 0; i<col; i++){
		for (j = 0; j<M[0][i]; j++)
			matI[(maxVal-1)-j][i] = 0;
	}
	
	ImWrite(imgHist, "histo.pgm");
	MatWriteAsc(histo, "chenille-hist.mx");
	
	/* Exercice 3 */
	
	// moyenne hist
	int moy = 0;
	row = ImNbRow(imgGris);
	col = ImNbCol(imgGris);
	for (i = 0; i<256; i++){
		moy = moy + i*M[0][i];
	}
	moy = moy / (row*col);
	matI = ImGetI(imgGris);
	
	Image imgBin = ImAlloc(BitMap,row,col);
	unsigned char **matB = ImGetI(imgBin);
	
	for (i = 0; i<row; i++)
		for (j = 0; j<col; j++)
			if (matI[i][j] > moy)
				matB[i][j] = 1;
			else
				matB[i][j] = 0;
	
	ImWrite(imgBin, "bin.pgm");
	
	MatFree(&histo);
	ImFree(&imgHist);
	ImFree(&imgGris);
	
		
	return 0;
}
