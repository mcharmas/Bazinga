#ifndef BCONNECTIONEXCEPTION_H
#define BCONNECTIONEXCEPTION_H

#include <QString>
#include "ClientLib_global.h"
#include "bdatagram.h"

class CLIENTLIBSHARED_EXPORT BConnectionException
{
public:
	BConnectionException(char * cause, BDatagram * datagram = NULL);
	BConnectionException(const QString & cause, BDatagram * datagram = NULL);
	BConnectionException(BConnectionException & old);
	~BConnectionException();
	const QString toString();
	BDatagram * getDatagram();
private:
	QString cause;
	BDatagram * datagram;
};

#endif // BCONNECTIONEXCEPTION_H
