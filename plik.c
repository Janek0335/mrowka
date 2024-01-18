#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include "matrix.h"
#include "mrowka.h"

int* wyznaczRozmiar(FILE *in){
    int znak;
    rewind(in);
    int a = 0;
    int b = 1;
    int* rozmiar = malloc(2*sizeof(int));
    while (znak = fgetc(in) != '\n'){
        a++;
    }
    while (znak = fgetc(in) != EOF){
        if (znak == '\n'){
            b++;
        }
    }
    rozmiar[0] = a-2;
    rozmiar[1] = b-2;
    return rozmiar;
}

void wczytaj(FILE *in, int a, int b, mrowka* mrowka1, Matrix *mat){ // a to ilosc rzedow, b to ilosc kolumn wczytywanej planszy (bez obramowania)
    rewind(in);
    wchar_t znak;
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++){
            znak = fgetwc(in);
            wprintf(L"%lc", znak);
            switch(znak){
                case ' ':
                    mat->data[i][j] = 0;
                    break;
                case '█':
                    mat->data[i][j] = 1;
                    break;
                case '△':
                    mat->data[i][j] = 0;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 0;
                    break;
                case '▲':
                    mat->data[i][j] = 1;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 0;
                    break;
                case '▷':
                    mat->data[i][j] = 0;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 90;
                    break;
                case '▶':
                    mat->data[i][j] = 1;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 90;
                    break;
                case '▽':
                    mat->data[i][j] = 0;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 180;
                    break;
                case '▼':
                    mat->data[i][j] = 1;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 180;
                    break;
                case '◁':
                    mat->data[i][j] = 0;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 270;
                    break;
                case '◀':
                    mat->data[i][j] = 1;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 270;
                    break;
                case WEOF:
                    break;
                default:
                    continue;
                }
            }
        }
    }

void zapisz(FILE *out, mrowka* mrowka1, Matrix *mat){
    fprintf(out,"┌");
    for (int k = 0; k < mat->c; k++){
        fprintf(out,"─");
    }
    fprintf(out, "┐\n");
    for (int i = 0; i < mat->r; i++){
        fprintf(out, "│");
        for (int j = 0; j < mat->c; j++){
            if (i == mrowka1->pozX && j == mrowka1->pozY){ //jesli akurat tu jest mrowka
                switch(mrowka1->zwrot){
                    case 0:
                        if (mat->data[i][j] == 0) fprintf(out,"△");
                        else if (mat->data[i][j] == 1) fprintf(out,"▲");
                        break;
                    case 90:
                        if (mat->data[i][j] == 0) fprintf(out,"▷");
                        else if (mat->data[i][j] == 1) fprintf(out,"▶");
                        break;
                    case 180:
                        if (mat->data[i][j] == 0) fprintf(out,"▽");
                        else if (mat->data[i][j] == 1) fprintf(out,"▼");
                        break;
                    case 270:
                        if (mat->data[i][j] == 0) fprintf(out,"◁");
                        else if (mat->data[i][j] == 1) fprintf(out,"◀");
                        break;
                }
            }
            else{
            switch(mat->data[i][j]){ //jesli tu nie ma mrowki
                case 0:
                    fprintf(out," ");
                    break;
                case 1:
                    fprintf(out,"█");
                    break;
                }
            }
        }
        fprintf(out,"│\n");
    }
    fprintf(out,"└");
    for (int k = 0; k < mat->c; k++){
        fprintf(out,"─");
    }
    fprintf(out,"┘");
}