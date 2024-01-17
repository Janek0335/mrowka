#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "matrix.h"
#include "mrowka.h"
#include "plik.h"

// zera to biale pola, jedynki to czarne
int main(int argc, char **argv){
  int i = 0;
  int opt;
  int rows = 5;
  int collumns = 5;
  int iteracji = 5;
  char* outputFile;
  int doFile = 0;
  double fillRatio = 0;
  char nazwaPliku[100];
  char *fileWithMap;
  FILE *fname;
  
  while((opt = getopt(argc, argv, ":r:c:i:f:hw:o:")) != -1){
    switch (opt)
    {
      case 'o':
        doFile = 1;
        outputFile = optarg;
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
      case 'w':
        fillRatio = atof(optarg);
        break;
      case 'f':
        fileWithMap = optarg;
        break;
      case 'h':
          printf("Wywolanie programu:\n./ mrowka[-r wiersze][-c kolumny][-i iteracje][-w % zapelnienia][-f nazwaPlikuWejsciowego][-o nazwaPlikuWyjsciowego][-h]\nOpcje:\n");
          printf("r - rows / liczba wierszy\n");
          printf("c - columns/ liczba kolumn\n");
          printf("i - iterations/ liczba iteracji\n");
          printf("f - fileWithMap / nazwa pliku wejsciowego z mapa\n");
          printf("h - help/ wyswietlana pomoc\n");
          printf("w - fillRatio/ wypelnienie planszy\n");
          printf("o - outputFile / plik wyjsciowy do zapisu\n");
            
        break;
      case '?':
        printf("Nieznana opcja: %c\t Zajrzyj do help -h\n", optopt);
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
  while (i < iteracji){ //wykonujemy iteracje tak dlugo az zostana wykonane wszystkie lub wyjdziemy za plansze (if czyKoniec to sprawdza)
    printf("Iteracja numer %d\n",i);
    zmienKolor(mrowka1,plansza); //faktycznie
    printf("Ziterowano mrowke\n");
    
    normalizacjaKataMrowki(mrowka1);
    ruchDoPrzoduMrowki(mrowka1);
  
    //Zapis do pliku tu dolozyc
    if(doFile){
      sprintf(nazwaPliku, "%s_%d", outputFile, i);
      fname = fopen(nazwaPliku, "w");
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
