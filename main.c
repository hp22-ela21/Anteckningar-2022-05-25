/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/*************************************************************************
* Returnerar ett slumptal mellan 0 - 100. För att erhålla ett slumptal
* anropas funktionen rand från biblioteket stdlib.
*************************************************************************/
static inline double get_random(void) { return (double)(rand() % 101); }

/*************************************************************************
* Fyller en array till bredden med randomiserade flyttal. 
* För iterationen används en dubbelpekare döpt i som börjar på första
* index (i = data) och slutar där arrayen tar slut (data + size).
* Ett flyttal tilldelas till adressen som i pekar på via en derefens *i.
*************************************************************************/
static void assign(double* data, const size_t size)
{
   for (register double* i = data; i < data + size; ++i)
      *i = get_random();
   return;
}

/*************************************************************************
* Skapa en funktion döpt print för att skriva ut arrayens innehåll.
* Passera en pekare till arrayen, arrayens storlek samt vilket typ av
* stream / filpekare vi skall använda (konsol eller fil).
*************************************************************************/
static void print(const double* data, const size_t size, FILE* stream)
{
   if (!stream) stream = stdout;
   fprintf(stream, "-----------------------------------------------------------\n");
   for (register const double* i = data; i < data + size; ++i)
      fprintf(stream, "%g\n", *i);
   fprintf(stream, "-----------------------------------------------------------\n\n");
   return;
}

/*************************************************************************
* Deklarerar en array döpt data som rymmer tio flyttal. Fyller sedan
* denna array till bredden med tio randomiserade tal. Skriver sedan ut
* dessa tal i konsolen. Bifogar sedan innehållet till en textfil 
* döpt data.txt. Stänger sedan filen, vilket dock hade genomförts
* automatiskt när programmet avslutats. Det är dock bra att ha som
* vana att alltid stänga filerna manuellt.
*************************************************************************/
int main(void)
{
   double data[10];
   assign(data, 10);
   print(data, 10, stdout);
   FILE* fstream = fopen("data.txt", "a");
   print(data, 10, fstream);
   fclose(fstream);
   return 0;
}