#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "matrix.h"
#include "mrowka.h"

// zera to biale pola, jedynki to czarne
int main(int argc, char **argv){
  int i = 0;
  int opt;
  int rows = 5;
  int collumns = 5;
  int iteracji = 5;
  char* filen;
  int doFile = 0;
  char nazwaPliku[100];
  FILE *fname;
  
  while((opt = getopt(argc, argv, ":r:c:i:f:")) != -1){
    switch (opt)
    {
      case 'f':
        doFile = 1;
        filen = optarg;
        break;
      case 'r':
        rows = atoi(optarg);
        break;
      case 'c':
        collumns = atoi(optarg);
        break;
      case 'i':
        iteracji = atoi(optarg);
        break;
      case '?':
        printf("Nieznana opcja: %c\n", optopt);
        break;
      case ':':
        printf("Brak wartosci do opcji");
        break;
      default:
        fprintf(stderr, "Nie powinnismy tu trafic");
    }
  }

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
    if(doFile){
      sprintf(nazwaPliku, "%s_%d", filen, i);
      fname = fopen(nazwaPliku, "w"); //tutaj zmiana printToScreen powinna byc, aby zwracalo najlepiej plansze a nie printy same i void
      fclose(fname);
    }

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
