#include "bconnection.h"
#include "bconnectionexception.h"

#include <QDateTime>
#include <QThread>
#include <QDebug>

CLIENTLIBSHARED_EXPORT BConnection::BConnection(unsigned char clientType)
	: clientType(clientType)
{
	startTimer(B_INTERVAL_ACK_MS);
}

void BConnection::connect(const QString &serverAddress, quint16 serverPort, QString login, QString password, quint16 listeningPort, QString token) {
	qDebug() << "Sending SREQ";
	hostAddress.setAddress(serverAddress);
	hostPort = serverPort;
	this->listeningPort = listeningPort;

	socket.bind(listeningPort);

	QByteArray arr((login + ":" + password
					+ ":" + listeningPort
					+ ":" + token).toAscii());

	BDatagram dgramLogin((quint32) 0,
						 clientType,
						 (quint32) QDateTime::currentDateTime().toTime_t(),
						 (unsigned char)B_TYPE_SREQ, arr);

	QByteArray * datagram = dgramLogin.getAllData();

	socket.writeDatagram(*datagram, hostAddress, serverPort);
	delete datagram;
}


int BConnection::sendData(BDatagram &data) {
	QByteArray * datagram = data.getAllData();
	int status = socket.writeDatagram(*datagram, hostAddress, hostPort);
	delete datagram;
	return status;
}

void BConnection::timerEvent(QTimerEvent * e) {
	if(sessid != 0) {
		qDebug() << "Sending CHECK";
		QByteArray empty;
		BDatagram dgramAck(sessid, clientType,
						   (quint32) QDateTime::currentDateTime().toTime_t(),
						   (unsigned char)B_TYPE_CHECK, empty);
		QByteArray * datagram = dgramAck.getAllData();

		socket.writeDatagram(*datagram, hostAddress, hostPort);
		delete datagram;
	}
}

BDatagram * BConnection::getData() {
	int size = socket.pendingDatagramSize();
	char * data = new char[size];
	QHostAddress senderAddr;
	quint16 senderPort;

	socket.readDatagram(data, size, &senderAddr, &senderPort);

	if (senderAddr != hostAddress && senderPort != hostPort) {
		qDebug() << "Bad sender: " << senderAddr << ":" << senderPort
				<< "; expected: " << hostAddress << ":" << hostPort;
		delete data;
		throw BConnectionException("Bad sender");

	} else {
		BDatagram * datagram = new BDatagram(data, size);
		delete data; // moze powodowac segfault jesli BDataArray nie kopiuje tego. powinno sie okazac po pierwszym odpaleniu

		if(datagram->source != B_SOURCE_SERVER) {
			delete datagram;
			throw BConnectionException("Packet not from server!");
		}

		switch (datagram->type) {
  case B_TYPE_SACK:
			if(sessid == 0) {
				sessid = datagram->sessid;
			} else {
				throw BConnectionException("Someone tried to inject different sessionid");
			}
			delete datagram;
			break;

  case B_TYPE_SDEN:
			sessid = 0;
			delete datagram;
			throw BConnectionException("Server disconnected.");
			break;

  case B_TYPE_ERROR:
			delete datagram;
			throw BConnectionException(QString(datagram->data));
			break;

			default:
			delete datagram;
		}
	}
	return NULL;
}

bool BConnection::isSessionAlive() {
	return sessid != 0;
}
