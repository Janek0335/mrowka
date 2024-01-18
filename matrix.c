#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Matrix * createMatrix(int r, int c) {
		int i;
		Matrix * mat = (Matrix*) malloc(sizeof(Matrix));
		if (mat != NULL) {
			mat->r = r;
			mat->c = c;
			mat->data = (int**) malloc(sizeof(int*) * r);
			for (i=0; i < r; i++) {
					mat->data[i] = (int*) malloc(sizeof(int) * c);
			}
		}

		return mat;
}

void freeMatrix(Matrix * mat) {
  int i;
	for (i=0;i < mat->r; i++)
		free(mat->data[i]);
	free(mat->data);
	free(mat);
}

int fillRandom(double percentBlack, Matrix* mat){
	if (percentBlack < 0 || percentBlack > 100){
		printf("Szansa musi byc z zakresu od 0 do 100, nie wykonano zadnej akcji\n");
		return -1;
	}
	else{
		srand((unsigned int) time(NULL));
		int szansa;
		for (int i = 0; i< mat->r; i++){
			for (int j = 0; j< mat->c; j++){
				szansa = rand() % 100 + 1;
				if (szansa <= percentBlack){
					mat->data[i][j] = 1;
				}
				else {
					mat->data[i][j] = 0;
				}
			}
		}
		return 0;
	}
}
