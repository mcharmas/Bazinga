#include "bob.h"

BOb::BOb(quint16 x, quint16 y, quint16 width, quint16 height)
	: x(x), y(y), width(width), height(height)
{}

BOb::BOb() : x(0), y(0), width(0), height(0)
{}

BOb::BOb(QByteArray &arr, int offset)
{
	if(arr.size() < offset + 4 || offset < 0) {
		x = y = width = height = 0;
	} else {
		x = arr.at(offset);
		y = arr.at(offset + 1);
		width = arr.at(offset + 2);
		height = arr.at(offset + 3);
		int rest = arr.at(offset + 4);

		/* 3 to binarnie 11, przesuwamy jako maske do wyciagania
		   kolejnych bitow po 2.
		   pozniej przesuwamy to o potrzebna ilosc miejsc, by znalazlo sie
		   jako 9-ty i 10-ty bit liczby.
		 */
		x      |= (rest & (3 << 6)) << 2;
		y      |= (rest & (3 << 4)) << 4;
		width  |= (rest & (3 << 2)) << 6;
		height |= (rest &  3      ) << 8;
	}
}

void BOb::appendToArray(QByteArray &arr) const
{
	char arrayTmp[] = { x & 0xff,
						y & 0xff,
						width & 0xff,
						height & 0xff,
						0 /* miejsce na "reszte" */ };

	/* wyciagamy bity 10 i 9 i przesuwamy je w odpowiednie miejsce.
	*/

	int rest = 0;
	quint16 mask = 3 << 8;

	rest |= (     x & mask) >> 2;
	rest |= (     y & mask) >> 4;
	rest |= ( width & mask) >> 6;
	rest |= (height & mask) >> 8;
	arrayTmp[4] = rest & 0xff;

	arr.append(arrayTmp, 5);
}
