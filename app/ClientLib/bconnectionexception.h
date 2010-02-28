#ifndef BCONNECTIONEXCEPTION_H
#define BCONNECTIONEXCEPTION_H

#include <QString>
#include "ClientLib_global.h"
#include "bdatagram.h"

/*! \brief Klasa opisujaca wyjatek polazenia z serwerem Bazinga.

  Moze zawierac w sobie datagram powodujacy problem.
  */
class CLIENTLIBSHARED_EXPORT BConnectionException
{
public:
	/*! \brief Utworz wyjatek z podana przyczyna i datagramem */
	BConnectionException(char * cause, BDatagram * datagram = NULL);

	/*! \brief Utworz wyjatek z podana przyczyna i datagramem */
	BConnectionException(const QString & cause, BDatagram * datagram = NULL);

	/*! \brief Konstruktor kopiujacy. Przejmuje datagram po starym.
	W old datagram ustawiany jest na NULL */
	BConnectionException(BConnectionException & old);

	/*! \brief Destruktor, kasuje ew. datagram */
	~BConnectionException();

	/*! \brief Zwraca opis wyjatku

	\return powod + informacja czy jest w wyjatku zawarty datagram.
	*/
	const QString toString();

	/*! \brief Zwraca datagram.

	  Ewentualnego datagramu nie nalezy usuwac. Zrobi to destruktor wyjatku.

	  \return Jesli nie ma datagramu, zwraca NULL.
	  */
	BDatagram * getDatagram();
private:
	QString cause;
	BDatagram * datagram;
};

#endif // BCONNECTIONEXCEPTION_H
