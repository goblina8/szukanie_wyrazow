#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 20
#define ILOSC 100
#define K 1000

//DEKLARACJA FUNKCJI
void czytaj(FILE *plik, char wzorzec[MAX]);
void wyswietl(int linia, char linijka[K], char tab[K]);
int wzor(char slowo[MAX], char wzorzec[MAX], int s, int w);
int dlugosc(char slowo[MAX]);
int levenshtein(char slowo[MAX], char wzorzec[MAX], int s, int w);
int czeski(char slowo[MAX], char wzorzec[MAX], int w);
int minimum(int a, int b, int c);

//MAIN
int main()
{
  FILE *plik;                // uchwyt do pliku
  char nazwa[ILOSC];         // nazwa pliku do wczytania
  char wzorzec[MAX];         // wzorzec
  int i;                     // zmienna pomocnicza
  int warunek_plik = 1;      // warunek wyjscia
  int warunek_wzor = 0;      // warunek_wyjscia
  int warunek_wyjscia = 1;   // warunek wyjscia z programu
  int prawidlowy = 1;        // czy wzorzec jest poprawny
  system("clear");
  while (warunek_wyjscia)
    {
      while(warunek_plik)
	{
	  printf("Aby wyjsc z programu wpisz 1\n");
	  printf("Podaj plik do wczytania\n");
	  scanf("%s", nazwa);
	  plik=fopen(nazwa, "r");
	  if (plik != NULL)
	    {
	      printf("Poprawnie wczytano plik\n");;
	      warunek_plik = 0;
	      warunek_wzor = 1;
	    }
	  else
	    {
	      if ((nazwa[0] == '1') && (nazwa[1] == NULL))
		{
		  warunek_plik = 0;
		  warunek_wyjscia = 0;
		  fclose(plik);
		  system("clear");
		  printf("Wyjscie z programu\n");
		}
	      else
		{
		  system("clear");
		  printf("Taki plik nie istnieje\n");
		}
	    }
	}
      while (warunek_wzor)
	{
	  prawidlowy = 1;
	  printf("\n");
	  printf("Aby wyjsc z programu wpisz 1\n");
	  printf("Aby wybrac inny plik do odczytu wybierz 2\n");
	  printf("Podaj wzorzec:\n");
	  scanf("%s", wzorzec);
	  if ((wzorzec[0] == '2') && (wzorzec[1] == NULL))
	    {
	      for (i = 0; i < MAX; i++)
		{
		  wzorzec[i] = NULL; 
		}
	      for (i = 0; i < ILOSC; i++)
		{
		  nazwa[i] = NULL;
		}
	      warunek_wzor = 0;
	      warunek_plik = 1;
	      prawidlowy = 0;
	    }
	  if ((wzorzec[0] == '1') && (wzorzec[1] == NULL))
	      {
		warunek_wzor = 0;
		warunek_plik = 0;
		prawidlowy = 0;
		warunek_wyjscia = 0;
		system("clear");
		printf("Wyjscie z programu\n");
	      }
	  if (prawidlowy == 1)
	    {
	      for (i = 0; wzorzec[i] != 0; i++)
		{
		  if (isalpha(wzorzec[i]) == 0)
		    {
		      wzorzec[i+1] = NULL;
		      prawidlowy = 0;
		      printf("Wzorzec moze zawierac tylko litery\n");
		    }
		}
	    }
	  if (prawidlowy != 0)
	    {
	      system("clear");
	      printf("Nazwa pliku: %s\n", nazwa);
	      printf("Wzorzec: %s\n", wzorzec);
	      printf("\n");
	      plik=fopen(nazwa, "r");
	      czytaj(plik, wzorzec);
	      for (i = 0; i < MAX; i++)
		{
		  wzorzec[i] = NULL; 
		}
	    }
	  fclose(plik);
	}
    }
  return 0;
} //main

//FUNKCJE

int wzor(char slowo[MAX], char wzorzec[MAX], int s, int w)
{
  int odleglosc;
  if (slowo[0] != NULL)
    {
      odleglosc = levenshtein(slowo, wzorzec, s, w); //sprawdzenie jak duza roznica miedzy slowami
      if (odleglosc <= 2)
	{
	  if (odleglosc == 0) //slowo == wzorzec
	    {
	      return 1;
	    }
	  else
	    {
	      if (odleglosc == 1) //nadmiar, niedomiar lub zamiana 1 litery 
		{
		  return 1;
		}
	      if ((odleglosc == 2) && (s == w) && (czeski(slowo, wzorzec, w) == 1))//jesli czeski blad to wyswietl, w innym wypadku nie
		{
		  return 1;
		}
		
	    }
	}
    }
  return 0;
}

void wyswietl(int linia, char linijka[K], char tab[K])
{
  int ilosc = 0; // ilosc ' ' do wyprintfowania
  if(linia < 9)
    {
      ilosc = 1;
    }
  else
    {
      if (linia < 99)
	{
	  ilosc = 2;
	}
      else
	{
	  if (linia < 999)
	    {
	      ilosc = 3;
	    }
	  else
	    if (linia < 9999)
	      {
		ilosc = 4;
	      }
	    else
	      if(linia < 99999)
		{
		  ilosc = 5;
		}
	}
    }
  printf("%d  ", linia);
  printf("%s", linijka);
  for(int i = 0; i < ilosc+2; i++)
    {
      printf(" ");
    }
  printf("%s\n", tab);
}

int minimum(int a, int b, int c)
{
  if (a < b)
    {
      if (a < c)
	{
	  return a;
	}
      else
	{
	  return c;
	}
    }
  else
    {
      if (b < c)
	{
	  return b;
	}
      else
	{
	  return c;
	}
    }
}

int dlugosc(char slowo[MAX])
 {
   int dlugosc = 0;
   for (int i = 0; slowo[i] != NULL; i++)
     {
       dlugosc++;
     }
   return dlugosc;
 }

int levenshtein (char slowo[MAX], char wzorzec[MAX], int s, int w)
{
  s++;
  w++;
  int d[s][w]; // odleglosc
  int i;       // wiersze
  int j;       // kolumny
  int c;       // koszt 
 
  for (i = 0; i < s; i++)
    {
      for (j = 0; j < w; j++)
	{
	  if (i == 0)
	    {
	      if (j == 0)
		{
		  d[i][j] = 0;
		}
	      else
		{
		  d[i][j] = j;
		}
	    }
	  else
	    {
	      if (j == 0)
		{
		  d[i][j] = i;
		}
	      else
		{
		  if (slowo[j-1] == wzorzec[i-1])
		    {
		      c = 0;
		    }
		  else
		    {
		      c = 1;
		    }
		  d[i][j] = minimum((d[i-1][j] + 1), (d[i][j-1] + 1), (d[i-1][j-1] + c));
		}
	    }
	 }
    }
  return d[s-1][w-1];
}

int czeski(char slowo[MAX], char wzorzec[MAX], int w)
{
  int i;
  int blad = 0;
  for (i = 0; i < w; i++)
    {
      if (slowo[i] != wzorzec[i])
	{
	  if ((slowo[i] == wzorzec[i+1]) && (slowo[i+1] == wzorzec[i]))
	    {
	      blad++;
	      i++;
	    }
	}
    }
  return blad;
}

void czytaj(FILE *plik, char wzorzec[MAX])
{
  int s, w;               // dlugosci slowa i wzorca 
  int i, j;               // zmienna pomocnicza
  int g = 0;              // ktory z kolei znak w linii
  int linia = 0;          // numer kolejnej linii
  int czy_wyswietlic = 0; // czy wyswietlic dana linie (1 - tak, 0 - nie)
  char ciag[MAX];         // pobrane przez scanf
  char slowo[MAX];        // pojedyncze slowo
  char linijka[K];        // pobrane przez fgets
  char tab[K];            // tabela kolejnych znakow ' ' i '^' - czyli co podkreslic
  w = dlugosc(wzorzec);
  
  while (1)
    {
      fgets(linijka, K, plik);
      if(feof(plik) != 0)
	{
	  break;
	}
      else
	{
	  linia++;
	}
      while (linijka[g] != '\n')
	{
	  sscanf(linijka + g, "%s", ciag);
	  i = 0;
	  j = 0;
	  while (ciag[i] != NULL)
	    {
	      if (isalpha(ciag[i]) != 0)
		{
		  slowo[j] = ciag[i];
		  j++;
		}
	      i++;
	    }
	  s = dlugosc(slowo);
	  if (wzor(slowo, wzorzec, s, w) == 1)
	    {
	      for (i = 0; i < dlugosc(ciag); i++)
		{
		  tab[g] = '^';
		  g++;
		}
	      czy_wyswietlic = 1;
	    }
	  else
	    {
	      for (i = 0; i < dlugosc(ciag); i++)
		{
		  tab[g] = ' ';
		  g++;
		}
	    }
	  if (linijka[g] == ' ')
	    {
	      tab[g] = ' ';
	      g++;
	    }
	  for (i = 0; i < MAX; i++)
	    {
	      slowo[i] = NULL;
	      ciag[i] = NULL;
	    }
	} //while
      if (czy_wyswietlic == 1)
	{
	  wyswietl(linia, linijka, tab);
	}
      for (i = 0; i < K; i++)
	{
	  tab[i] = NULL;
	  linijka[i] = NULL;
	}
      czy_wyswietlic = 0;
      g = 0;
    } //while
} //czytaj

//SPRAWOZDANIE

/*
ZADANIE DODATKOWE 23.01.2021r
Gabriela Kaczmarek (259234)

Program ma na celu wyszukiwanie przybliżone (znajduje słowa różniące się od wzorca o odległość Levenshteina nie większa niż dwa. Tzn, rozpoznaje błąd czeski, widzi słowa z nadmiarową literą, lub te, którym jakiejś brakuje, rozpoznaje także literówki. Znalezione słowa zbliżone do wzorca wypisuje wraz z linijką tekstu, w której się znalazły i jej numerem. Wyszukane słowa podkreśla z pomocą '^'.

By poprawnie testować menu użytkownika trzeba było wprowadzać zarówno dane poprawne, jak i niepoprawne, by zobaczyć jak zachowa się program, czy w odpowiednim momencie "cofnie", do poprzedniego "okna", czy wyjdzie z programu, otworzy plik (czy da komunikat, że taki plik nie istnieje) itp.

Aby testować program użyłam Księgi 1 Pana Tadeusza. Kolejno za wzorzec podawalam różne słowa, różnej długości, zarówno zawierające literówki, nadmierna literę, błąd czeski lub posiadające listerę na mało (każdą rzecz starałam się sprawdzić, dla różnego jej umiejscowienia w danym słowie (np. szukając słowa "laty", za wzorzec podawałam "ltay", "lty", "laaty", "layt", "lrty" itp.)). 

Wyszukiwanie tego typu miało na celu sprawdzenie, jak program reaguje na różne gługości wzorca podczas wyszukiwania słów, oraz jak dobrze radzi sobie z błędami, które miał rozpoznawać, podczas wyszukiwania słów.

Danymi wejściowymi do programu był więc plik i wzorzec, danymi oczekiwanymi na wyjściu: numer i treść linii wraz z podkreślonymi w niej słowami, które należało wyszukać. 

Jeśli zaś chodzi o rezultat - program zdaje się działać zgodnie z założeniami.*/

