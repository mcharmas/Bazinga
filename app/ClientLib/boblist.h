#ifndef BOBLIST_H
#define BOBLIST_H

#include <QList>
#include "bob.h"

class BObList : public QList<BOb>
{
public:
	BObList(QByteArray & arr);
	BObList();

	QByteArray * pack();
};

#endif // BOBLIST_H
