#include <stdio.h>
#include <stdlib.h>
#include "mrowka.h"
#include "matrix.h"

mrowka * stworzMrowke(int zwrot, int pozX, int pozY){ //alokacja miejsca na mrowke wraz z poczatkowymi parametrami
    mrowka *mrowka1 = malloc(sizeof(mrowka*));
		if (mrowka1 == NULL) {
            fprintf(stderr, "Nie udalo sie zaalokowac pamieci na mrowke\n");
            return NULL;
        }
    return mrowka1;
}

void zmienKolor(mrowka* mrowka1, Matrix *mat){ //wykonanie manewru zmiany koloru miejsca na ktorym stoi mrowka
    fprintf(stderr, "Zmienilxm kolor");
    if (mat->data[mrowka1->pozX][mrowka1->pozY] == 0){
        mat->data[mrowka1->pozX][mrowka1->pozY] = 1;
        mrowka1->zwrot += 90;
    }
    else if (mat->data[mrowka1->pozX][mrowka1->pozY] == 1){
        mat->data[mrowka1->pozX][mrowka1->pozY] = 0;
        mrowka1->zwrot -= 90;
    }
}

void normalizacjaKataMrowki(mrowka *mrowka1){ //upewnienie sie ze parametr zwrot mrowki jest z zakresu <0,359> stopni, czyli jest 0 (gora), 90 (prawo), 180 (dol), 270 (lewo)
    if (mrowka1->zwrot < 0){
        mrowka1->zwrot += 360;
        mrowka1->zwrot %= 360;
    }
    else if (mrowka1->zwrot > 359){
        mrowka1->zwrot -= 360;
    }
}

void ruchDoPrzoduMrowki(mrowka *mrowka1){ //wykonanie ruchu mrowki przed siebie (w zaleznosci od tego w ktora strone sie patrzy)
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

int czyKoniec (mrowka *mrowka1, Matrix *mat){ //sprawdzenie czy mrowka nie wyszla poza plansze, bo wtedy program ma sie skonczyc. zwraca 1 jesli wyszla, 0 jesli nie
    int koniec = 0;
    if (mrowka1->pozX < 0 || mrowka1->pozX > mat->r || mrowka1->pozY < 0 || mrowka1->pozY > mat->c){
        koniec = 1;
    }
    return koniec;
}

void freeMrowka(mrowka*mrowka1){ //zwolnienie pamieci zaalokowanej na mrowke
    free(mrowka1);
}