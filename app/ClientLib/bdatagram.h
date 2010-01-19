#ifndef BDATAGRAM_H
#define BDATAGRAM_H

#include "ClientLib_global.h"

#include <QByteArray>
class BDatagram
{
public:
	BDatagram(int sessid, unsigned char source, int timestamp, unsigned char type, QByteArray & data);
	int sessid;
	unsigned char source;
	int timestamp;
	unsigned char type;
	QByteArray data;
};

#endif // BDATAGRAM_H
