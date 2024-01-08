#include "matrix.h"
typedef struct _Mrowka { //mrowka ma swoj zwrot (0,90,180,270), pozycja w osi X i Y na dwuwymiarowej mapie
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