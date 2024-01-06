#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "mrowka.h"
// zera to biale pola, jedynki to czarne
int main(int argc, char **argv){
  int i = 0;
  int rows = atoi(argv[1]);
  int collumns = atoi(argv[2]);
  int iteracji = atoi(argv[3]);
  Matrix *plansza = createMatrix(rows,collumns);
  fillBlankMatrix(plansza);
  printf("Oryginalna plansza:\n");
  printToScreen(plansza);
  mrowka *mrowka1 = stworzMrowke(0,collumns/2,rows/2);
  
  while (i < iteracji){
    printf("Iteracja numer %d\n",i);
    zmienKolor(mrowka1,plansza); //tu jest najwyrazniej pierwsza komenda ktora nie jest wykonywana
    printf("Ziterowano mrowke\n");
    normalizacjaKataMrowki(mrowka1);
    ruchDoPrzoduMrowki(mrowka1);
    i++;
    if (czyKoniec(mrowka1, plansza) == 1){
      return 0;
    }
    printf("Konczymy? : %d\n",czyKoniec(mrowka1, plansza));
  }
  
  printf("Koncowa plansza:\n");
  printToScreen(plansza);
  freeMatrix(plansza);
  freeMrowka(mrowka1);
  return 0;
}
