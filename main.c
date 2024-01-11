#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "mrowka.h"
// zera to biale pola, jedynki to czarne
int main(int argc, char **argv){
  int i = 0;
  int rows = argc > 1 ? atoi(argv[1]) : 5;
  int collumns = argc > 2 ? atoi(argv[2]) : 5;
  int iteracji = argc > 3 ? atoi(argv[3]) : 5;
  char* filen = "test";
  FILE *fname;
  fprintf(stderr, "poczatek");
  Matrix *plansza = createMatrix(rows,collumns);
  fillBlankMatrix(plansza);
  printf("Oryginalna plansza:\n");
  printToScreen(plansza);
  mrowka *mrowka1 = stworzMrowke(0,collumns/2,rows/2);
  fprintf(stderr, "stworzylxm mrowke");
  while (i < iteracji){ //wykonujemy iteracje tak dlugo az zostana wykonane wszystkie lub wyjdziemy za plansze (if czyKoniec to sprawdza)
    printf("Iteracja numer %d\n",i);
    zmienKolor(mrowka1,plansza); //faktycznie
    printf("Ziterowano mrowke\n");
    
    normalizacjaKataMrowki(mrowka1);
    ruchDoPrzoduMrowki(mrowka1);

    //Zapis do pliku
    fname = fopen(("%s_%d", filen, i), "w");
    fprintf(fname, "test%d", i); //tutaj zmiana printToScreen powinna byc, aby zwracalo najlepiej plansze a nie printy same i void
    fclose(fname);

    i++;
    if (czyKoniec(mrowka1, plansza) == 1){
      break;
    }
    printf("Konczymy? : %d\n",czyKoniec(mrowka1, plansza));
  }
  
  printf("Koncowa plansza:\n");
  printToScreen(plansza);
  freeMatrix(plansza);
  freeMrowka(mrowka1);
  return 0;
}
