/***********************************************************************************
* R�ttad kod f�r uppgift p� repetitionsduggan 2022-05-25. Inline-kommentarer 
* anv�nds f�r att markera korrigeringar i koden.
***********************************************************************************/

/* Inkluderingsdirektiv: */
#include <stdio.h>

/***********************************************************************************
* Bifogar ett flyttal till en fil. Filen �ppnas f�r bifogande av text. Om filen
* inte gick att �ppna avslutas funktionen. Annars skrivs talet till filen.
* N�r skrivningen �r slutf�rd st�ngs filen och funktionen avslutas.
***********************************************************************************/
static void file_append(const char* filepath, const double number)
{
   FILE* fstream = fopen(filepath, "a"); /* Tog bort dereferensen p� filepath (str�ngar skall ej derefereras). */
   if (!fstream) return; /* Bytte FILE mot fstream, d� vi vill unders�ka ifall filen gick att �ppna. */
   fprintf(fstream, "%g\n", number); /* Tog bort adressoperatorn p� number, d� vi inte vill skriva ut adressen. */
   fclose(fstream); /* St�nger filen. */
   return;
}

/***********************************************************************************
* L�ser in varje rad fr�n en fil och skriver ut i konsolen. Om filen inte gick att
* �ppna avslutas funktionen. Annars l�ses varje rad in en efter en och lagras
* tempor�rt i en str�ng d�pt s, vars inneh�ll skrivs ut i konsolen.
* N�r l�sningen �r slutf�rd st�ngs filen och funktionen avslutas.
***********************************************************************************/
static void file_read(const char* filepath)
{
   FILE* fstream = fopen(filepath, "r"); /* Bytte w mot r, d� vi vill l�sa fr�n filen. */
   if (!fstream) return; /* Bytte FILE mot fstream, d� vi vill unders�ka ifall filen gick att �ppna. */
   char s[100]; /* S�tter utrymme till 100 tecken i st�llet f�r 1, s� ett tecken �r f�r lite (10 minst). */
   s[0] = '\0'; /* Initierar str�ngen genom att tilldela sluttecknet i b�rjan (flyttas bak�t n�r text bifogas). */
   while (fgets(s, sizeof(s), fstream)) /* L�ser fr�n filen i st�llet f�r konsolen (fstream i st�llet f�r stdin). */
      fprintf(stdout, "%s", s); /* Skriver ut i konsolen i st�llet f�r till filen (stdout i st�llet f�r fstream). */
   fclose(fstream); /* St�nger filen. */
   return;
}

/***********************************************************************************
* Bifogar flyttal 3.4 samt 4.5 till filen numbers.txt. L�ser sedan filens
* inneh�ll och skriver ut i konsolen.
***********************************************************************************/
int main(void)
{
   file_append("numbers.txt", 3.4);
   file_append("numbers.txt", 4.5);
   file_read("numbers.txt");
   return 0;
}
