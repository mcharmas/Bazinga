#ifndef BDATAGRAM_H
#define BDATAGRAM_H

#include "ClientLib_global.h"

#include <QByteArray>
class BDatagram
{
public:
	BDatagram(quint32 sessid, unsigned char source, quint32 timestamp, unsigned char type, QByteArray & data);
	BDatagram(char * dataIn, int size);

	QByteArray * getAllData();

	quint32 sessid;
	unsigned char source;
	quint32 timestamp;
	unsigned char type;
	QByteArray data;

};

#endif // BDATAGRAM_H
