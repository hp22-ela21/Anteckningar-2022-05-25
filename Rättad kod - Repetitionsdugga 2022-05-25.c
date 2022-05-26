/***********************************************************************************
* Rättad kod för uppgift på repetitionsduggan 2022-05-25. Inline-kommentarer 
* används för att markera korrigeringar i koden.
***********************************************************************************/

/* Inkluderingsdirektiv: */
#include <stdio.h>

/***********************************************************************************
* Bifogar ett flyttal till en fil. Filen öppnas för bifogande av text. Om filen
* inte gick att öppna avslutas funktionen. Annars skrivs talet till filen.
* När skrivningen är slutförd stängs filen och funktionen avslutas.
***********************************************************************************/
static void file_append(const char* filepath, const double number)
{
   FILE* fstream = fopen(filepath, "a"); /* Tog bort dereferensen på filepath (strängar skall ej derefereras). */
   if (!fstream) return; /* Bytte FILE mot fstream, då vi vill undersöka ifall filen gick att öppna. */
   fprintf(fstream, "%g\n", number); /* Tog bort adressoperatorn på number, då vi inte vill skriva ut adressen. */
   fclose(fstream); /* Stänger filen. */
   return;
}

/***********************************************************************************
* Läser in varje rad från en fil och skriver ut i konsolen. Om filen inte gick att
* öppna avslutas funktionen. Annars läses varje rad in en efter en och lagras
* temporärt i en sträng döpt s, vars innehåll skrivs ut i konsolen.
* När läsningen är slutförd stängs filen och funktionen avslutas.
***********************************************************************************/
static void file_read(const char* filepath)
{
   FILE* fstream = fopen(filepath, "r"); /* Bytte w mot r, då vi vill läsa från filen. */
   if (!fstream) return; /* Bytte FILE mot fstream, då vi vill undersöka ifall filen gick att öppna. */
   char s[100]; /* Sätter utrymme till 100 tecken i stället för 1, så ett tecken är för lite (10 minst). */
   s[0] = '\0'; /* Initierar strängen genom att tilldela sluttecknet i början (flyttas bakåt när text bifogas). */
   while (fgets(s, sizeof(s), fstream)) /* Läser från filen i stället för konsolen (fstream i stället för stdin). */
      fprintf(stdout, "%s", s); /* Skriver ut i konsolen i stället för till filen (stdout i stället för fstream). */
   fclose(fstream); /* Stänger filen. */
   return;
}

/***********************************************************************************
* Bifogar flyttal 3.4 samt 4.5 till filen numbers.txt. Läser sedan filens
* innehåll och skriver ut i konsolen.
***********************************************************************************/
int main(void)
{
   file_append("numbers.txt", 3.4);
   file_append("numbers.txt", 4.5);
   file_read("numbers.txt");
   return 0;
}
