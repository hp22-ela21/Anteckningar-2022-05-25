/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/*************************************************************************
* Returnerar ett slumptal mellan 0 - 100. F�r att erh�lla ett slumptal
* anropas funktionen rand fr�n biblioteket stdlib.
*************************************************************************/
static inline double get_random(void) { return (double)(rand() % 101); }

/*************************************************************************
* Fyller en array till bredden med randomiserade flyttal. 
* F�r iterationen anv�nds en dubbelpekare d�pt i som b�rjar p� f�rsta
* index (i = data) och slutar d�r arrayen tar slut (data + size).
* Ett flyttal tilldelas till adressen som i pekar p� via en derefens *i.
*************************************************************************/
static void assign(double* data, const size_t size)
{
   for (register double* i = data; i < data + size; ++i)
      *i = get_random();
   return;
}

/*************************************************************************
* Skapa en funktion d�pt print f�r att skriva ut arrayens inneh�ll.
* Passera en pekare till arrayen, arrayens storlek samt vilket typ av
* stream / filpekare vi skall anv�nda (konsol eller fil).
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
* Deklarerar en array d�pt data som rymmer tio flyttal. Fyller sedan
* denna array till bredden med tio randomiserade tal. Skriver sedan ut
* dessa tal i konsolen. Bifogar sedan inneh�llet till en textfil 
* d�pt data.txt. St�nger sedan filen, vilket dock hade genomf�rts
* automatiskt n�r programmet avslutats. Det �r dock bra att ha som
* vana att alltid st�nga filerna manuellt.
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