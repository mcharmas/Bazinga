#ifndef BCONNECTIONBLOCKER_H
#define BCONNECTIONBLOCKER_H

#include "ClientLib_global.h"

#include <QString>

/*! \brief Blokuje albo zezwala na nawiazanie polaczenia w BConnectionWidget.

	Klasa dziedziczaca moze zaimplementowac metody canConnect() i canDisconnect()
	zeby zablokowac laczenie/rozlaczenie w wybranych przypadkach
  */
class CLIENTLIBSHARED_EXPORT BConnectionBlocker
{
public:
    BConnectionBlocker();

	/*! \brief Zezwala/zabrania nawiazanie polaczenia

	  @return domyslna implementacja zwraca true
	  */
	virtual bool canConnect();

	/*! \brief Zezwala/zabrania zerwanie polaczenia

	  @return domyslna implementacja zwraca true
	  */

	virtual bool canDisconnect();
	/*! \brief Zwraca komunikat ostatniego bledu
	  */

	virtual QString toString();

	virtual ~BConnectionBlocker();
};

#endif // BCONNECTIONBLOCKER_H
