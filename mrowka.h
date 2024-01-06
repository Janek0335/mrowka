#include "matrix.h"
typedef struct _Mrowka {
				int zwrot;
				int pozX;
                int pozY;
} mrowka;

mrowka * stworzMrowke(int zwrot, int pozX, int pozY);
void zmienKolor(mrowka* mrowka1, Matrix *mat);
void normalizacjaKataMrowki(mrowka *mrowka1);
void ruchDoPrzoduMrowki(mrowka *mrowka1);
int czyKoniec (mrowka *mrowka1, Matrix *mat);
void freeMrowka(mrowka *mrowka1);