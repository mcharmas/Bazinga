#ifndef BOB_H
#define BOB_H

#include "ClientLib_global.h"
#include <QByteArray>

/*! \brief Klasa reprezenujaca polozenie obiektu (BOb(ject)) i jego wielkosc

  Poniewaz dosc standardowa rozdzielczoscia kamer internetowych jest 640x480:

	\li x i width musza byc rzutowane na przedzial 0-639
	\li y i height musza byc rzutowane na przedzial 0-479

	Technicznie kazda liczba reprezentowana jest jako 10 bitow unsigned.
  */
class CLIENTLIBSHARED_EXPORT BOb
{
public:
	/*! \brief Tworzy obiekt z podanych liczb
	  */
	BOb(quint16 x, quint16 y, quint16 width, quint16 height);

	/*! \brief Pusty konstruktor */
	BOb();

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

	/*! \brief Zwraca stringa w postaci [x, y, w, h] */
	QString toString() const;

	/*! \brief Wspolrzedna X

	  Wartosc musi byc z przedzialu 0-639.
	  */
	quint16 x;

	/*! \brief Wspolrzedna Y

	  Wartosc musi byc z przedzialu 0-479.
	  */
	quint16 y;

	/*! \brief Szerokosc obiektu

	  Wartosc musi byc z przedzialu 0-639.
	  */
	quint16 width;

	/*! \brief Wysokosc obiektu

	  Wartosc musi byc z przedzialu 0-479.
	  */
	quint16 height;
};

#endif // BOB_H
