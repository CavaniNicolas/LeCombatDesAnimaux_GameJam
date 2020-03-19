
#include <stdio.h>
#include <stdlib.h>
#include "optimiseDisplay.h"

//modifie (optimise) les valeurs de lines et columns si elles sont = 0.
void setOptimizedLinesAndColumns(int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm) {
	if (*nbColumns > 0 && *nbLines > 0) {
		printf("Ne pas entrer à la fois nbColumns et nbLines > 0\n"\
			   "(Ne pas appliquer de contraintes sur les deux paramètres en même temps)\n"\
			   "Mettre 0 pour une optimisation automatique d'une ou des deux variables\n");
		optimizeNumberOfLinesColumns(wBlock, hBlock, nbChara, fillPercent, nbLines, nbColumns, sizeSideIm);

	} else {

		if (*nbColumns > 0) {

			setSecondVariable(*nbColumns, nbLines, sizeSideIm, nbChara, fillPercent, wBlock, hBlock);

		} else if (*nbLines > 0){

			setSecondVariable(*nbLines, nbColumns, sizeSideIm, nbChara, fillPercent, wBlock, hBlock);

		} else {
			optimizeNumberOfLinesColumns(wBlock, hBlock, nbChara, fillPercent, nbLines, nbColumns, sizeSideIm);
		}

	}
}


void setSecondVariable(int varCte, int * varAdapting, int * sizeSideIm, int nbChara, float fillPercent, int wBlock, int hBlock) {
	int sizeSideImX = 0;
	int sizeSideImY = 0;

	// varCte, varAdapting : nombre de lignes ou de colonnes, l'une est fixe et détermine la valeur de l'autre
	*varAdapting = nbChara / varCte;
	if (nbChara%varCte != 0) {
		(*varAdapting) ++;
	}

	sizeSideImX = fillPercent * wBlock / varCte;
	sizeSideImY = fillPercent * hBlock / *varAdapting;
	*sizeSideIm  = (sizeSideImX < sizeSideImY)? sizeSideImX : sizeSideImY; // side of the square
}


//calcul le nombre optimal de lignes et colonnes
void optimizeNumberOfLinesColumns(int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm) {
	int good = 0;

	*nbColumns = nbChara;
	*nbLines   = 1;

	int sImX = 0;
	int sImY = 0;

	int sImNouv = 0;
	int ecartSImNouv = 0;

	int sImAncien = 0;
	int ecartSImAncien = (hBlock > wBlock)? hBlock : wBlock;; //max entre hBlock et hBlock

	while (good == 0) {
		sImX = fillPercent * wBlock / *nbColumns;
		sImY = fillPercent * hBlock / *nbLines;
		sImNouv = (sImX < sImY)? sImX : sImY;
		ecartSImNouv = abs(sImX - sImY);

		if (ecartSImNouv > ecartSImAncien) {
			good = 1;

			// on remet les bonnes valeurs de ligne et de colonne correspondantes aux bonnes valeurs de sizeSideIm
			(*nbColumns)++;
			(*nbLines)--;


		} else {
			sImAncien = sImNouv;
			ecartSImAncien = ecartSImNouv;
			(*nbColumns)--;
		}


		if (*nbColumns == 0) {
			good = 1;
			(*nbColumns)++;
		}
		if (*nbLines == 0) {
			good = 1;
			(*nbLines)++;
		}
		if (*nbColumns * *nbLines < nbChara) {
			(*nbLines)++;
		}
	}
	*sizeSideIm = sImAncien;

	printf("colonne = %d, ligne = %d \n", *nbColumns, * nbLines);

}
