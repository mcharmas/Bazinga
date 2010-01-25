#ifndef BCONNECTIONEXCEPTION_H
#define BCONNECTIONEXCEPTION_H

#include <QString>

class BConnectionException
{
public:
	BConnectionException(char * cause);
	BConnectionException(const QString & cause);
	const QString & toString();
private:
	QString cause;
};

#endif // BCONNECTIONEXCEPTION_H
