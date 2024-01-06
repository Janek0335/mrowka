#include <stdio.h>
#include <stdlib.h>
#include "mrowka.h"
#include "matrix.h"

mrowka * stworzMrowke(int zwrot, int pozX, int pozY){
    mrowka * mrowka1 = (mrowka*) malloc(sizeof(mrowka));
		if (mrowka1 == NULL) {
            fprintf(stderr, "Nie udalo sie zaalokowac pamieci na mrowke\n");
        }
    return mrowka1;
}

void iteracjaMrowki(mrowka* mrowka1, Matrix *mat, int pozX, int pozY){
    if (mat->data[pozX][pozY] == 0){
        mat->data[pozX][pozY] = 1;
        mrowka1->zwrot += 90;
    }
    else if (mat->data[pozX][pozY] == 1){
        mat->data[pozX][pozY] = 0;
        mrowka1->zwrot -= 90;
    }
}

void normalizacjaKataMrowki(mrowka *mrowka1){
    if (mrowka1->zwrot < 360){
        mrowka1->zwrot += 360;
        mrowka1->zwrot %= 360;
    }
    else if (mrowka1->zwrot > 359){
        mrowka1->zwrot -= 360;
    }
}

void ruchDoPrzoduMrowki(mrowka *mrowka1){
    //rusza sie o 1 punkt do przodu wzgledem swojego zwrotu
    switch(mrowka1->zwrot){
        case 0:
            mrowka1->pozY += 1;
        case 90:
            mrowka1->pozX += 1;
        case 180:
            mrowka1->pozY -= 1;
        case 270:
            mrowka1->pozX -= 1;
    }
}

int czyKoniec (mrowka *mrowka1, Matrix *mat){
    int koniec = 0;
    if (mrowka1->pozX < 0 || mrowka1->pozX > mat->r || mrowka1->pozY < 0 || mrowka1->pozY > mat->c){
        koniec = 1;
    }
    return koniec;
}