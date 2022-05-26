/***********************************************************************************
* Notering om standardenheter i C, som alla utg�r filpekare (FILE*):
* 
* stdout => standardutenheten (utskrift i konsolen)
* stdin  => standardinenheten (inl�sning fr�n konsolen).
* stderr => standardfelenheten (utskrift till vald felenhet, default �r konsolen).
* 
* Notering om funktionen doubleptr-delete. Adressen till pekaren som pekare p� det
* dynamiska minnet passeras f�r att kunna s�tta denna till en nullpekare efter 
* deallokeringen. Annars om pekaren till f�ltet f�rs�ker passeras direkt s� kommer 
* enbart en kopia av denna fram. Minnet kan d� frig�ras, d� �ven kopian pekar p� 
* adressen till det dynamiskt allokerade minnet, men den ursprungliga pekaren kan ej 
* s�ttas till null. Originalet kommer d� forts�tta peka d�r det dynamiska minnet
* tidigare l�g. N�r adressen till pekaren passeras, s� utg�r dubbelpekaren som 
* kommer fram en kopia, men dereferensen av denna utg�rs av den egentliga pekaren.
* D�rmed kan pekaren s�ttas till null.
***********************************************************************************/

/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************************
* Returnerar pekare till dynamiskt allokerat f�lt av valbar storlek.
***********************************************************************************/
static inline double* doubleptr_new(const size_t size) 
{ 
   return (double*)malloc(sizeof(double) * size); 
}

/***********************************************************************************
* Frig�r minne f�r dynamiskt f�lt och s�tter f�ltets pekare till null.
***********************************************************************************/
static inline void doubleptr_delete(double** self) 
{ 
   free(*self); 
   *self = 0; 
   return;
}

/***********************************************************************************
* Returnerar ett flyttal mellan angivet min och max.
***********************************************************************************/
static inline double get_random(const double min, const double max)
{  
   return ((double)rand() / RAND_MAX) * (max - min) + min;
}

/***********************************************************************************
* Fyller ett f�lt med randomiserade flyttal inom angivet intervall.
***********************************************************************************/
static void assign(double* data, const size_t size, const double min, const double max)
{
   for (register double* i = data; i < data + size; ++i)
      *i = get_random(min, max);
   return;
}

/***********************************************************************************
* Sorterar inneh�ll i ett flyttalsf�lt i stigande ordning. Iteratation sker 
* genom f�ltet via en pekare i, som pekar p� varje tal fr�n f�rsta till n�st 
* sista i f�ltet. Det tal pekaren i pekar p� j�mf�rs mot samtliga efterf�ljande 
* tal, som pekas p� av pekare j. Om det tal pekare i pekar p� �r st�rre �n det tal 
* som pekare j pekar p�, s� byter talen plats, s� att det mindre talet placeras
* l�ngre fram i f�ltet.
***********************************************************************************/
static void sort(double* data, const size_t size)
{
   for (register double* i = data; i < data + size - 1; ++i)
   {
      for (register double* j = i + 1; j < data + size; ++j)
      {
         if (*i > *j)
         {
            const double temp = *i;
            *i = *j;
            *j = temp;
         }
      }
   }
   return;
}

/***********************************************************************************
* Skriver ut inneh�llet ur ett f�lt inneh�llande flyttal via en valbar datastr�m.
***********************************************************************************/
static void print(const double* data, const size_t size, FILE* stream)
{
   if (!stream) stream = stdout;
   fprintf(stream, "--------------------------------------------------------------------\n");
   for (register const double* i = data; i < data + size; ++i)
      fprintf(stream, "%g\n", *i);
   fprintf(stream, "--------------------------------------------------------------------\n\n");
   return;
}

/***********************************************************************************
* L�ser inneh�ll fr�n en fil rad f�r rad och skriver ut i konsolen. Vid fel skrivs
* ett felmeddelande ut via standardfelenheten stderr, som vanligtvis utg�rs av
* konsolen (kan v�ljas utefter behov, exempelvis till en fil via en filstr�m d�pt
* fstream, vilket kan �stadkommas genom att skriva *stderr = *fstream).
***********************************************************************************/
static void file_read(const char* filepath)
{
   FILE* fstream = fopen(filepath, "r");
   char s[100];

   if (!fstream)
   {
      fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
      return;
   }

   s[0] = '\0';
   while (fgets(s, sizeof(s), fstream))
      fprintf(stdout, "%s", s);
   fclose(fstream);
   return;
}

/***********************************************************************************
* Fyller en dynamisk array med 100 flyttal mellan -10 upp till 10. Sorterar sedan
* f�ltets inneh�ll i stigande ordning. Skriver sedan inneh�llet till en fil d�pt
* numbers.txt. Filens inneh�ll l�ses sedan in rad f�r rad och skrivs ut i konsolen.
***********************************************************************************/
int main(void)
{
   double* data = doubleptr_new(100);
   FILE* fstream = fopen("numbers.txt", "w");
   assign(data, 100, -10, 10);
   sort(data, 100);
   print(data, 100, fstream);
   fclose(fstream);
   file_read("numbers.txt");
   return 0;
}


