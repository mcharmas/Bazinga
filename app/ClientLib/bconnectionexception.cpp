#include "bconnectionexception.h"

BConnectionException::BConnectionException(char *cause) : cause(cause)
{
}
BConnectionException::BConnectionException(const QString & cause) : cause(cause)
{
}

const QString & BConnectionException::toString() {
	return cause;
}
