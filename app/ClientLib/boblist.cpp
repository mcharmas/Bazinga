#include "boblist.h"
#include <QListIterator>

BObList::BObList()
{
}

BObList::BObList(QByteArray &arr)
{}

QByteArray * BObList::pack()
{
	QByteArray * array = new QByteArray();
	QListIterator<BOb> it(*this);
	while(it.hasNext()) {
		it.next().appendToArray(*array);
	}
	return array;
}
