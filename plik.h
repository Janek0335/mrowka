#ifndef _PLIK_H
#define _PLIK_H

#include "matrix.h"
#include "mrowka.h"
#include <stdio.h>

int* wyznaczRozmiar(FILE*);
void zapisz(FILE*, mrowka*, Matrix*);
void wczytaj(FILE* , int , int , mrowka* , Matrix*);

#endif