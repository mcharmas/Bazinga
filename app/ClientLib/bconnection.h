#ifndef BCONNECTION_H
#define BCONNECTION_H

#include "ClientLib_global.h"

#include "bdatagram.h"

#include <QUdpSocket>
#include <QHostAddress>

class BConnection
{
public:

    BConnection();

protected:
	/**
	  Binduje podany port (listeningPort), laczy sie z serwerem na podanym porcie, loguje na podstawie podanych danych
	  */
	int connect(const QString & hostname, quint16 port, QString login, QString password, quint16 listeningPort, QString token);
	int sendData(BDatagram & data);

	BDatagram * getData();

private:
	QHostAddress hostAdress;
	QUdpSocket socket;
};

#endif // BCONNECTION_H
