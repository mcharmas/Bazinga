#ifndef BCONNECTION_H
#define BCONNECTION_H

#include "ClientLib_global.h"

#include "bdatagram.h"

#include <QUdpSocket>
#include <QHostAddress>

class BConnection
{
public:

	BConnection(unsigned char clientType);

protected:
	/**
	  connect w trybie klienta
	  Binduje podany port (listeningPort), laczy sie z serwerem na podanym porcie, loguje na podstawie podanych danych
	  */
	void connect(const QString & address,
				 quint16 port,
				 QString login,
				 QString password,
				 quint16 listeningPort,
				 QString token);

	int sendData(BDatagram & data);

	BDatagram * getData();

private:
	QHostAddress hostAddress;
	quint16 listeningPort;
	quint16 hostPort;
	QUdpSocket socket;
	int sessid;
	unsigned char clientType;
};

#endif // BCONNECTION_H
