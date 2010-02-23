#include "bconnectionexception.h"

BConnectionException::BConnectionException(char *cause, BDatagram * datagram)
	: cause(cause), datagram(datagram)
{
}
BConnectionException::BConnectionException(const QString & cause, BDatagram * datagram)
	: cause(cause), datagram(datagram)
{
}

BConnectionException::BConnectionException(BConnectionException &old)
	: cause(old.cause), datagram(old.datagram)
{
	old.datagram = NULL;
}

BConnectionException::~BConnectionException() {
	if(datagram) delete datagram;
}

const QString BConnectionException::toString() {
	return cause + (datagram ? " (Datagram avialable)" : "");
}

BDatagram * BConnectionException::getDatagram() {
	return datagram;
}
