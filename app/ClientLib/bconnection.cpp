#include "bconnection.h"
#include "bconnectionexception.h"

#include <QDateTime>
#include <QThread>
#include <QDebug>

BConnection::BConnection(unsigned char clientType)
	: clientType(clientType)
{
}

void BConnection::connect(const QString &address, quint16 port, QString login, QString password, quint16 listeningPort, QString token) {
	hostAddress.setAddress(address);
	hostPort = port;
	this->listeningPort = listeningPort;

	socket.bind(listeningPort);

	QByteArray arr((login + ":" + password
					+ ":" + listeningPort
					+ ":" + token).toAscii());

	BDatagram dgramLogin((quint32) 0,
						 clientType,
						 (quint32) QDateTime::currentDateTime().toUTC().toTime_t(),
						 (unsigned char)B_TYPE_SREQ, arr);

	QByteArray * datagram = dgramLogin.getAllData();

	socket.writeDatagram(*datagram, hostAddress, port);
	delete datagram;
}


int BConnection::sendData(BDatagram &data) {
	QByteArray * datagram = data.getAllData();
	int status = socket.writeDatagram(*datagram, hostAddress, hostPort);
	delete datagram;
	return status;
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
		delete data;
		if(datagram->source != B_SOURCE_SERVER) {
			delete datagram;
			throw BConnectionException("Packet not from server!");
		}
		switch (datagram->type) {
  case B_TYPE_SACK:
			sessid = datagram->sessid;
			delete datagram;
			break;
  case B_TYPE_SDEN:
			sessid = 0;
			delete datagram;
			throw BConnectionException("Server disconnected.");
			break;
  case B_TYPE_CHECK:
			// TODO: odsylanie pinga do serwera?
			break;
  case B_TYPE_ERROR:
			break;
		}
	}
	return 0;
}
