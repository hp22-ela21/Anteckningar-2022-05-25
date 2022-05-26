/***********************************************************************************
* Notering om standardenheter i C, som alla utgör filpekare (FILE*):
* 
* stdout => standardutenheten (utskrift i konsolen)
* stdin  => standardinenheten (inläsning från konsolen).
* stderr => standardfelenheten (utskrift till vald felenhet, default är konsolen).
* 
* Notering om funktionen doubleptr-delete. Adressen till pekaren som pekare på det
* dynamiska minnet passeras för att kunna sätta denna till en nullpekare efter 
* deallokeringen. Annars om pekaren till fältet försöker passeras direkt så kommer 
* enbart en kopia av denna fram. Minnet kan då frigöras, då även kopian pekar på 
* adressen till det dynamiskt allokerade minnet, men den ursprungliga pekaren kan ej 
* sättas till null. Originalet kommer då fortsätta peka där det dynamiska minnet
* tidigare låg. När adressen till pekaren passeras, så utgör dubbelpekaren som 
* kommer fram en kopia, men dereferensen av denna utgörs av den egentliga pekaren.
* Därmed kan pekaren sättas till null.
***********************************************************************************/

/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************************
* Returnerar pekare till dynamiskt allokerat fält av valbar storlek.
***********************************************************************************/
static inline double* doubleptr_new(const size_t size) 
{ 
   return (double*)malloc(sizeof(double) * size); 
}

/***********************************************************************************
* Frigör minne för dynamiskt fält och sätter fältets pekare till null.
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
* Fyller ett fält med randomiserade flyttal inom angivet intervall.
***********************************************************************************/
static void assign(double* data, const size_t size, const double min, const double max)
{
   for (register double* i = data; i < data + size; ++i)
      *i = get_random(min, max);
   return;
}

/***********************************************************************************
* Sorterar innehåll i ett flyttalsfält i stigande ordning. Iteratation sker 
* genom fältet via en pekare i, som pekar på varje tal från första till näst 
* sista i fältet. Det tal pekaren i pekar på jämförs mot samtliga efterföljande 
* tal, som pekas på av pekare j. Om det tal pekare i pekar på är större än det tal 
* som pekare j pekar på, så byter talen plats, så att det mindre talet placeras
* längre fram i fältet.
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
* Skriver ut innehållet ur ett fält innehållande flyttal via en valbar dataström.
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
* Läser innehåll från en fil rad för rad och skriver ut i konsolen. Vid fel skrivs
* ett felmeddelande ut via standardfelenheten stderr, som vanligtvis utgörs av
* konsolen (kan väljas utefter behov, exempelvis till en fil via en filström döpt
* fstream, vilket kan åstadkommas genom att skriva *stderr = *fstream).
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
* fältets innehåll i stigande ordning. Skriver sedan innehållet till en fil döpt
* numbers.txt. Filens innehåll läses sedan in rad för rad och skrivs ut i konsolen.
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


