#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct _Matrix {
				int r,c;
				int **data;
} Matrix;

Matrix * readFromFile(char * fname);
void printToScreen(Matrix *mat);

Matrix * createMatrix(int r, int c);
void freeMatrix(Matrix *mat);
void fillBlankMatrix(Matrix * mat);
int fillRandom(double percentBlack, Matrix* mat);
#endif