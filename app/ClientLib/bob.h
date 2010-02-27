#ifndef BOB_H
#define BOB_H

#include "ClientLib_global.h"
#include <QByteArray>

/*! \brief Klasa reprezenujaca polozenie obiektu (BOb(ject)) i jego wielkosc

  Poniewaz dosc standardowa rozdzielczoscia kamer internetowych jest 640x480:

	\li x i width musza byc rzutowane na przedzial 0-639
	\li y i height musza byc rzutowane na przedzial 0-479

  */
class CLIENTLIBSHARED_EXPORT BOb
{
public:
	/*! \brief Tworzy obiekt z podanych liczb
	  */
	BOb(quint16 x = 0, quint16 y = 0, quint16 width = 0, quint16 height = 0);

	/*! \brief Tworzy obiekt z danych w tablicy

	  Obiekt tworzac sie przeczyta kolejnych 5 bajtow tablicy. Traktujac
	je nastepujaco:

	\li Z pierwszych 4 bajtow czyta po 8 mlodszych bitow kazdej liczby (x,y...)
	\li Z ostatniego bajtu czyta po 2 starsze bity z kazdej liczby

	  @param arr tablica, z ktorej ma byc czytane
	  @param offset przesuniecie w tabeli od miejsca w ktorym ma czytac.
	  */
	BOb(QByteArray & arr, int offset);

	/*! \brief Zapisuje obiekt na koniec podanej tablicy

	  Zapis jest prowadzony zgodnie z formatem opisanym w konstruktorze BOb(QByteArray & arr, int offset) .

	  @param arr Tablica do ktorej ma sie dodac.
	  */
	void appendToArray(QByteArray & arr) const;

	quint16 x, y, width, height;
};

#endif // BOB_H
