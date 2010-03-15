#ifndef BOBLIST_H
#define BOBLIST_H

#include <QList>
#include "bob.h"

/*! \brief Lista obiektow BOb

  Pakuje i wypakowuje obiekty BOb z tablicy bajtow.
  Dziedzy po QList, mozna wiec uzywac wszystkich metod/iteratorow dla QList.
  */
class CLIENTLIBSHARED_EXPORT BObList : public QList<BOb>
{
public:
	/*! \brief Czyta pakiety z tablicy bajtow.

	  Kazdy obiekt ma po 5 bajtow, wiec zakladana ilosc obiektow jest arr.size() / 5.
	  */
	BObList(QByteArray & arr);

	/*! \brief Tworzy pusta tablice BOb-ow.
	  */
	BObList();

	/*! \brief Pakuje obiekty do tablicy bajtow i zwraca te tablice.

	  Tablica ma rozmiar ilosc obiektow * 5 bajtow.
	  */
	QByteArray * pack();

	/*! \brief Zwraca liste obiektow w postaci stringa */
	QString toString() const;
};

#endif // BOBLIST_H
