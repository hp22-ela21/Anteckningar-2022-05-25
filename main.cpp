/* Inkluderingsdirektiv: */
#include <iostream> /* Inmatning och utskrift. */
#include <string> /* Dynamiska str�ngar. */
#include <vector> /* Dynamisk vektorklass. */
#include <fstream> /* Filstr�msklass. */
#include <cstdlib> /* C:s standardbibliotek. */

/*************************************************************************
* Returnerar ett slumptal mellan 0 - 100. F�r att erh�lla ett slumptal
* anropas funktionen rand fr�n biblioteket stdlib.
*************************************************************************/
static inline double get_random(void) { return (double)(rand() % 101); }

/*****************************************************************************
* Tilldelar flyttal till en dynamisk vektor. Ing�ende argument data utg�r
* en referens till vektorn i fr�ga. Referenser fungerar som pekare, men 
* anv�nds som vanliga variabler. D�rmed beh�vs ej derefenser, 
* adressoperatorer och dylikt. 

* H�r tilldelas flyttalen vid index, men det hade g�tt lika bra med pekare 
* via f�ljande for-sats:
* for (auto i = data.begin(); i < data.end(); ++i)
*    *i = get_random();
*****************************************************************************/
static void assign(std::vector<double>& data)
{
   for (std::size_t i = 0; i < data.size(); ++i)
      data[i] = get_random();
   return;
}

/*****************************************************************************
* Skriver ut inneh�llet ur en vektor p� var sin rad via en valbar stream.
* Ing�ende argument data utg�r en referens till vektorn i fr�ga och stream
* utg�r aktuellt val av datastr�m, d�r standardutenheten std::cout utg�r
* default (man beh�ver ej passera en stream och d� anv�nds std::cout).
*
* En range-baserad for-loop anv�nds f�r att skriva ut varje element ur 
* vektorn. for (auto i : data) betyder "f�r alla element i vektorn data".
* Funktionen s�tts till ett funktionstemplate, d�r vektorn kan inneha valfri
* datatyp T. D�rmed kan denna funktion anv�ndas f�r utskrift av inneh�ll i
* en vektor av valfri datatyp.
*****************************************************************************/
template<class T>
static void print(const std::vector<T>& data, std::ostream& stream = std::cout)
{
   stream << "---------------------------------------------------------------------\n";
   for (auto i : data) 
      stream << i << "\n";
   stream << "---------------------------------------------------------------------\n\n";
   return;
}

/*****************************************************************************
* Skapar en dynamisk vektor som rymmer tio flyttal vid start via ett objekt
* av klassen vektor. Inneh�llet skrivs sedan ut i konsolen och bifogas  
* ocks� till en textfil d�pt data.txt. Filstr�mmen st�ngs automatiskt n�r
* motsvarande objekt, h�r d�pt fstream, g�r ur scope, s� st�nga filen 
* manuellt beh�vs ej h�r. Det kan dock g�ras via medlemsfunktionen close(),
* f�r objektet fstream hade det blivit implementerat som fstream.close().
*****************************************************************************/
int main(void)
{ 
   std::vector<double> data(10);
   assign(data);
   print(data);
   std::ofstream fstream("data.txt", std::ios::app);
   print(data, fstream);
   return 0;
}
