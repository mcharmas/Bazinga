#ifndef BCONNECTIONEXCEPTION_H
#define BCONNECTIONEXCEPTION_H

#include <QString>
#include "ClientLib_global.h"

class CLIENTLIBSHARED_EXPORT BConnectionException
{
public:
	BConnectionException(char * cause);
	BConnectionException(const QString & cause);
	const QString & toString();
private:
	QString cause;
};

#endif // BCONNECTIONEXCEPTION_H
