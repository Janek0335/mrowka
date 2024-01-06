#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "mrowka.h"
// zera to biale pola, jedynki to czarne
int main(int argc, char **argv){
  int rows = atoi(argv[1]);
  int collumns = atoi(argv[2]);
  int iteracji = atoi(argv[3]);
  Matrix *plansza = createMatrix(rows,collumns);
  fillBlankMatrix(plansza);
  printToScreen(plansza);
  stworzMrowke(0,0,0);
  freeMatrix(plansza);
  return 0;
}
