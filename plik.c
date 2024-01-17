#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "mrowka.h"

int* wyznaczRozmiar(FILE *in){
    int znak;
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
    int znak;
    for (int i = 0; i < a; i++){
        for (int j = 0; i < b; j++){
            znak = fgetc(in);
            switch(znak){
                case ' ':
                    mat->data[i][j] = 0;
                case '█':
                    mat->data[i][j] = 1;
                case '△':
                    mat->data[i][j] = 0;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 0;
                case '▲':
                    mat->data[i][j] = 1;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 0;
                case '▷':
                    mat->data[i][j] = 0;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 90;
                case '▶':
                    mat->data[i][j] = 1;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 90;
                case '▽':
                    mat->data[i][j] = 0;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 180;
                case '▼':
                    mat->data[i][j] = 1;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 180;
                case '◁':
                    mat->data[i][j] = 0;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 270;
                case '◀':
                    mat->data[i][j] = 1;
                    mrowka1->pozX = i;
                    mrowka1->pozY = j;
                    mrowka1->zwrot = 270;
                case EOF:
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
    fprintf(out, "┐");
    for (int i = 0; i < mat->r; i++){
        fprintf(out, "│");
        for (int j = 0; j < mat->c; j++){
            if (i == mrowka1->pozX && j == mrowka1->pozY){ //jesli akurat tu jest mrowka
                switch(mrowka1->zwrot){
                    case 0:
                        if (mat->data[i][j] == 0) fprintf(out,"△");
                        else if (mat->data[i][j] == 1) fprintf(out,"▲");
                    case 90:
                        if (mat->data[i][j] == 0) fprintf(out,"▷");
                        else if (mat->data[i][j] == 1) fprintf(out,"▶");
                    case 180:
                        if (mat->data[i][j] == 0) fprintf(out,"▽");
                        else if (mat->data[i][j] == 1) fprintf(out,"▼");
                    case 270:
                        if (mat->data[i][j] == 0) fprintf(out,"◁");
                        else if (mat->data[i][j] == 1) fprintf(out,"◀");
                }
        }
            else{
            switch(mat->data[i][j]){ //jesli tu nie ma mrowki
                case 0:
                    fprintf(out," ");
                case 1:
                    fprintf(out,"█");
            }
        }
    fprintf(out,"│");
    }
    fprintf(out,"└");
    for (int k = 0; k < mat->c; k++){
        fprintf(out,"─");
    }
    fprintf(out,"┘");
}
}