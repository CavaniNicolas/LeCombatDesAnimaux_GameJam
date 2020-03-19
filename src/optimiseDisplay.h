
#ifndef OPTIMISEDISLAY_H
#define OPTIMISEDISLAY_H


//calcul le nombre optimal de lignes et colonnes en fct du nombre total delements a placer et autorise de contraindre un des deux parametres
void setOptimizedLinesAndColumns(int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm);

// varCte, varAdapting : nombre de lignes ou de colonnes, l'une est fixe et détermine la valeur de l'autre
void setSecondVariable(int varCte, int * varAdapting, int * sizeSideIm, int nbChara, float fillPercent, int wBlock, int hBlock);

//calcul le nombre optimal de lignes et colonnes en fct du nombre total delements a placer
void optimizeNumberOfLinesColumns(int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm);


#endif
