#include <stdio.h>
#include "matrix.h"
// zera to biale pola, jedynki to czarne
int main(){
  int rows = 10;
  int collumns = 10;
  Matrix *plansza = createMatrix(rows,collumns);
  fillBlankMatrix(plansza);
  printToScreen(plansza);
  freeMatrix(plansza);
  return 0;
}
