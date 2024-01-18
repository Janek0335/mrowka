#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <locale.h>
#include <wchar.h>
#include "matrix.h"
#include "mrowka.h"
#include "plik.h"

// zera to biale pola, jedynki to czarne
int main(int argc, char **argv){
  setlocale(LC_ALL, "C.UTF-8");
  int i = 0;
  int opt;
  int rows = 10;
  int collumns = 10;
  int iteracji = 10;
  char* outputFile;
  int doFile = 0;
  int readFile = 0;
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
        readFile = 1;
        
        break;
      case 'h':
          printf("Wywolanie programu:\n./ mrowka[-r wiersze][-c kolumny][-i iteracje][-w ile zapelnienia <0, 100>][-f nazwaPlikuWejsciowego][-o nazwaPlikuWyjsciowego][-h]\nOpcje:\n");
          printf("r - rows / liczba wierszy\n");
          printf("c - columns/ liczba kolumn\n");
          printf("i - iterations/ liczba iteracji\n");
          printf("f - fileWithMap / nazwa pliku wejsciowego z mapa\n");
          printf("h - help/ wyswietlana pomoc\n");
          printf("w - fillRatio/ wypelnienie planszy\n");
          printf("o - outputFile / plik wyjsciowy do zapisu\n");
          return 0;
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
  mrowka *mrowka1;
  Matrix *plansza;
  if(readFile){
    fname = fopen(fileWithMap, "r");
    int* dane = wyznaczRozmiar(fname);
    collumns = dane[0];
    rows=dane[1];
    mrowka1 = stworzMrowke(0,collumns/2,rows/2);
    plansza = createMatrix(collumns,rows);
    wczytaj(fname, collumns+2, rows+2, mrowka1, plansza);
  }
  else{
    mrowka1 = stworzMrowke(0,collumns/2,rows/2);
    plansza = createMatrix(collumns,rows);
    if(fillRandom(fillRatio, plansza) == -1)
      return 1;
  }
  
  while (i < iteracji){ //wykonujemy iteracje tak dlugo az zostana wykonane wszystkie lub wyjdziemy za plansze (if czyKoniec to sprawdza)
    zmienKolor(mrowka1,plansza);
    normalizacjaKataMrowki(mrowka1);
    ruchDoPrzoduMrowki(mrowka1);
  
    //Zapis do pliku tu dolozyc
    if(doFile){
      snprintf(nazwaPliku, sizeof (nazwaPliku), "results/%s_%d", outputFile, i+1);
      fname = fopen(nazwaPliku, "w");
      zapisz(fname, mrowka1, plansza);
      fclose(fname);
    }
    else{
      zapisz(stdout, mrowka1, plansza);
    }
    i++;
    if (czyKoniec(mrowka1, plansza) == 1){
      break;
    }
  }
  freeMatrix(plansza);
  freeMrowka(mrowka1);
  return 0;
}
