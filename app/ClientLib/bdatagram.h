#ifndef BDATAGRAM_H
#define BDATAGRAM_H

#include "ClientLib_global.h"

#include <QByteArray>

/*! \brief Datagram zawierajacy generajuacy odpowiedenie naglowki.

  Oferuje bardzo podstawowa funkcjonalnosc. Obiekt ma dwa konstruktory dla wygody
  i metode getAllData() do wyciagania tablic typu QByteArray gotowych do wyslania
  (z odpowiednim naglowkiem).

  \warning Koduje liczby w kolejnosci bajtow little endian. Serwer jest na to przygotowany.

  Naglowek sklada sie z:
	\li 4 bajty unsinged little endian - ID sesji.
	\li 1 bajt unsinged - typ zrodla.
	\li 4 bajty unsinged little endian - timestamp.
	\li 1 bajt unsigned - typ komunikatu, jedno z B_TYPE_*
	\li 2 bajty unsinged little endian - rozmiar danych.
  */
class CLIENTLIBSHARED_EXPORT BDatagram
{
public:
	/*! \brief Tworzy obiekt na podstawie podanych parametrow. */
	BDatagram(quint32 sessid, //!< id sesji
			  unsigned char source, //!< typ zrolda
			  quint32 timestamp, //!< timestamp uniksowy.
			  unsigned char type, //!< typ komunikatu.
			  QByteArray & data /*!< tablica bajtow z danymi. */ );

	//! Tworzy obiekt z surowej tablicy bajtow o podanym rozmiarze.
	BDatagram(char * dataIn, int size);

	//! Pobiera datagram gotowy do wyslania na serwer
	QByteArray * getAllData();


	//! ID sesji, dopoki nie jest znany mozna wstawic 0.
	quint32 sessid;

	//! Typ zrodla: B_SOURCE_APP, B_SOURCE_DRIVER lub B_SOURCE_SERVER
	unsigned char source;

	//! timestamp uniksowy.
	quint32 timestamp;

	//! typ komunikatu.
	unsigned char type;

	//! tablica danych
	QByteArray data;

};

#endif // BDATAGRAM_H
