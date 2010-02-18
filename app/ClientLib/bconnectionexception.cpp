#include "bconnectionexception.h"

BConnectionException::BConnectionException(char *cause, BDatagram * datagram)
	: cause(cause), datagram(datagram)
{
}
BConnectionException::BConnectionException(const QString & cause, BDatagram * datagram)
	: cause(cause), datagram(datagram)
{
}

BConnectionException::~BConnectionException() {
	if(datagram) delete datagram;
}

const QString BConnectionException::toString() {
	if(datagram)
	return cause + " (Datagram avialable)";
}

BDatagram * BConnectionException::getDatagram() {
	return datagram;
}
