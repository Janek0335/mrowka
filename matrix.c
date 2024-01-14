#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Matrix * readFromFile(char * fname) {
				int r,c;
				int ir, ic;
				FILE * fin =  fopen(fname,"r");
				Matrix * mat = NULL;

				if (fin != NULL) {
					fscanf(fin,"%d %d",&r,&c);
					mat = createMatrix(r,c);
					if (mat != NULL) {
						for (ir = 0; ir < r; ir++) 
							for (ic = 0; ic < c; ic++)
								fscanf(fin, "%lf",&(mat->data[ir][ic]));
					} else {
								fprintf(stderr,"Wystąpił problem podczas tworzenia macierzy o rozmiarach %d x %d dla danych z pliku: %s\n", r, c, fname);
					}

					fclose(fin);
				} else {
								fprintf(stderr,"Nie mogę otworzyć pliku o nazwie: %s\n", fname);
				}

				return mat;
}

void printToScreen(Matrix *mat) {
	int i,j;
	printf("[ \n");
	for (i = 0; i<mat->r; i++) {
		printf("  ");
		for (j = 0; j < mat->c; j++) {
			printf("%d ", mat->data[i][j]);
		}
		printf("\n");
	}
	printf("]\n");
}

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

void fillBlankMatrix(Matrix * mat){
	for (int i = 0; i < mat->r; i++){
		for (int j = 0; j < mat->c; j++){
			mat->data[i][j] = 0;
		}
	}
}

void fillRandom(double percentBlack, Matrix* mat){
	if (percentBlack < 0 || percentBlack > 100){
		printf("Szansa musi byc z zakresu od 0 do 100");
		return NULL;
	}
	srand((unsigned int) time(NULL));
	int szansa;
	for (int i = 0; i< mat->r;){
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
}
