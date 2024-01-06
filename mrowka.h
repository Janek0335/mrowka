#include "matrix.h"
typedef struct _Mrowka {
				int zwrot;
				int pozX;
                int pozY;
} mrowka;

mrowka * stworzMrowke(int zwrot, int pozX, int pozY);
void iteracjaMrowki(mrowka* mrowka1, Matrix *mat, int pozX, int pozY);
void normalizacjaKataMrowki(mrowka *mrowka1);
void ruchDoPrzoduMrowki(mrowka *mrowka1);
int czyKoniec (mrowka *mrowka1, Matrix *mat);