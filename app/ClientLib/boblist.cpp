#include "boblist.h"
#include <QListIterator>

BObList::BObList()
{
}

BObList::BObList(QByteArray &arr)
{
	int size = (arr.size() / 5) * 5; // tak, zeby rozmiar byl podzielny przez 5.

	for(int i = 0; i < size; i += 5) {
		//tmp = new BOb(arr, i);
		append(BOb(arr, i));
	}
}

QByteArray * BObList::pack()
{
	QByteArray * array = new QByteArray();
	QListIterator<BOb> it(*this);
	while(it.hasNext()) {
		it.next().appendToArray(*array);
	}
	return array;
}
