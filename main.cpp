/* Inkluderingsdirektiv: */
#include <iostream> /* Inmatning och utskrift. */
#include <string> /* Dynamiska strängar. */
#include <vector> /* Dynamisk vektorklass. */
#include <fstream> /* Filströmsklass. */
#include <cstdlib> /* C:s standardbibliotek. */

/*************************************************************************
* Returnerar ett slumptal mellan 0 - 100. För att erhålla ett slumptal
* anropas funktionen rand från biblioteket stdlib.
*************************************************************************/
static inline double get_random(void) { return (double)(rand() % 101); }

/*****************************************************************************
* Tilldelar flyttal till en dynamisk vektor. Ingående argument data utgör
* en referens till vektorn i fråga. Referenser fungerar som pekare, men 
* används som vanliga variabler. Därmed behövs ej derefenser, 
* adressoperatorer och dylikt. 

* Här tilldelas flyttalen vid index, men det hade gått lika bra med pekare 
* via följande for-sats:
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
* Skriver ut innehållet ur en vektor på var sin rad via en valbar stream.
* Ingående argument data utgör en referens till vektorn i fråga och stream
* utgör aktuellt val av dataström, där standardutenheten std::cout utgör
* default (man behöver ej passera en stream och då används std::cout).
*
* En range-baserad for-loop används för att skriva ut varje element ur 
* vektorn. for (auto i : data) betyder "för alla element i vektorn data".
* Funktionen sätts till ett funktionstemplate, där vektorn kan inneha valfri
* datatyp T. Därmed kan denna funktion användas för utskrift av innehåll i
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
* av klassen vektor. Innehållet skrivs sedan ut i konsolen och bifogas  
* också till en textfil döpt data.txt. Filströmmen stängs automatiskt när
* motsvarande objekt, här döpt fstream, går ur scope, så stänga filen 
* manuellt behövs ej här. Det kan dock göras via medlemsfunktionen close(),
* för objektet fstream hade det blivit implementerat som fstream.close().
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
