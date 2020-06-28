
#include <stdio.h>
#include <stdlib.h>
#include "optimiseDisplay.h"


//modifie (optimise) les valeurs de lines et columns si elles sont = 0.
void setOptimizedLinesAndColumns(int wBlock, int hBlock, int nbObj, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm) {
	if (nbObj > 0) {
		if (*nbColumns > 0 && *nbLines > 0) {
			printf("Ne pas entrer à la fois nbColumns et nbLines > 0\n"\
				   "(Ne pas appliquer de contraintes sur les deux paramètres en même temps)\n"\
				   "Mettre 0 pour une optimisation automatique d'une ou des deux variables\n");
			optimizeNumberOfLinesColumns(wBlock, hBlock, nbObj, fillPercent, nbLines, nbColumns, sizeSideIm);

		} else {

			if (*nbColumns > 0) {

				setSecondVariable(*nbColumns, nbLines, sizeSideIm, nbObj, fillPercent, wBlock, hBlock);

			} else if (*nbLines > 0){

				setSecondVariable(*nbLines, nbColumns, sizeSideIm, nbObj, fillPercent, wBlock, hBlock);

			} else {
				optimizeNumberOfLinesColumns(wBlock, hBlock, nbObj, fillPercent, nbLines, nbColumns, sizeSideIm);
			}

		}
	} else {
		printf("Nombre d'objets a afficher negatifs ... Impossible\n");
	}
}


void setSecondVariable(int varCte, int * varAdapting, int * sizeSideIm, int nbObj, float fillPercent, int wBlock, int hBlock) {
	int sizeSideImX = 0;
	int sizeSideImY = 0;

	// varCte, varAdapting : nombre de lignes ou de colonnes, l'une est fixe et détermine la valeur de l'autre
	*varAdapting = nbObj / varCte;
	if (nbObj%varCte != 0) {
		(*varAdapting) ++;
	}

	sizeSideImX = fillPercent * wBlock / varCte;
	sizeSideImY = fillPercent * hBlock / *varAdapting;
	*sizeSideIm  = (sizeSideImX < sizeSideImY)? sizeSideImX : sizeSideImY; // side of the square
}


//calcul le nombre optimal de lignes et colonnes
void optimizeNumberOfLinesColumns(int wBlock, int hBlock, int nbObj, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm) {
	int good = 0;

	*nbColumns = nbObj;
	*nbLines   = 1;

	int sImX = 0;
	int sImY = 0;

	int sImNouv = 0;

	int sImAncien = 0;

	while (good == 0) {

		sImX = fillPercent * wBlock / *nbColumns;
		sImY = fillPercent * hBlock / *nbLines;
		sImNouv = (sImX < sImY)? sImX : sImY;

		if (sImNouv < sImAncien) {
			good = 1;

			// on remet la bonne valeur de colonnes correspondante a literation precedente (donc la bonne valeur de sizeSideIm)
			(*nbColumns)++;

		} else {
			sImAncien = sImNouv;
			(*nbColumns)--;
		}


		if (*nbColumns == 0) {
			good = 1;
			(*nbColumns)++;
		}

		*nbLines = nbObj / *nbColumns;
		if (nbObj % *nbColumns != 0) {
			(*nbLines) ++;
		}
	}

	*sizeSideIm = sImAncien;

	printf("colonne = %d, ligne = %d, sizeSideIm = %d\n", *nbColumns, *nbLines, *sizeSideIm);
}


// calcul la distance a placer entre deux objets
int spaceBetweenObjects(int nbLines, int sizeSideObj, int wBlock) {
	int totalSpaceUsed      = nbLines * sizeSideObj;
	int totalSpaceFree      = wBlock - totalSpaceUsed;
	int spaceBetweenObjects = totalSpaceFree / (2 * nbLines);
	return spaceBetweenObjects;
}


// calcul les nouveaux x et y de l'objets suivant a placer dans un block de coordonnées (0:0)
// et dont (le nombre de lignes et de colonnes) et sizeSideObj, XspaceBetweenObjects et YspaceBetweenObjects dépendent déjà des dimensions
void newOptimisedXY(int * X, int * Y, int * numLine, int * numColumn, int nbLines, int nbColumns, int sizeSideObj, int XspaceBetweenObjects, int YspaceBetweenObjects) {
	*numColumn += 1;

	/* calcul d'un saut de ligne nécessaire ou non */
	if (*numColumn <= nbColumns) {
		*X += sizeSideObj + 2 * XspaceBetweenObjects;
	} else {
		*X = XspaceBetweenObjects;
		*Y += sizeSideObj + 2 * YspaceBetweenObjects;
		numLine += 1;
		*numColumn = 1;
	}

}