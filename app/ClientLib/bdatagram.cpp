#include "bdatagram.h"

BDatagram::BDatagram(int sessid, unsigned char source, int timestamp, unsigned char type, QByteArray & data)
	: sessid(sessid),
	source(source),
	timestamp(timestamp),
	type(type),
	data(data)
{
}
