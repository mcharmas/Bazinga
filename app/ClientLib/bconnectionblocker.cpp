#include "bconnectionblocker.h"

BConnectionBlocker::BConnectionBlocker()
{
}

BConnectionBlocker::~BConnectionBlocker()
{
}

bool BConnectionBlocker::canConnect()
{
	return true;
}

bool BConnectionBlocker::canDisconnect()
{
	return true;
}

QString BConnectionBlocker::toString()
{
	QString str("Generic BConnectionBlockerClass::toString() (reimplement toString()).");
	return str;
}
