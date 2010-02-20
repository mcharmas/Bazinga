#ifndef BCONNECTION_H
#define BCONNECTION_H

#include "ClientLib_global.h"

#include "bdatagram.h"

#include <QUdpSocket>
#include <QHostAddress>

class CLIENTLIBSHARED_EXPORT BConnection : public QObject
{
	Q_OBJECT
public:

	BConnection(unsigned char clientType);
	bool isSessionAlive();

	/**
	  connect w trybie klienta
	  Binduje podany port (listeningPort), laczy sie z serwerem na podanym porcie, loguje na podstawie podanych danych
	  */
	void connect(const QString & serverAddress,
				 quint16 serverPort,
				 const QString & login,
				 const QString & password,
				 quint16 listeningPort,
				 const QString & token = QString());

	void disconnectFromHost();

	int sendData(BDatagram & data);
	int sendData(unsigned char command, QByteArray & data);
	int sendData(unsigned char command);

	BDatagram * getData();

signals:
	void connected(quint32 sessid);
	void disconnected();

private:
	void timerEvent(QTimerEvent *);
	QByteArray * newTMPdatagram(unsigned char command, QByteArray & data);

private:
	QHostAddress hostAddress;
	quint16 listeningPort;
	quint16 hostPort;
	QUdpSocket socket;
	quint32 sessid;
	unsigned char clientType;
};

#endif // BCONNECTION_H
