#include "bconnection.h"
#include "bconnectionexception.h"

#include <QDateTime>
#include <QThread>
#include <QDebug>

CLIENTLIBSHARED_EXPORT BConnection::BConnection(unsigned char clientType)
	: sessid(0), clientType(clientType)
{
	startTimer(B_INTERVAL_ACK_MS);
}

void BConnection::connect(const QString & serverAddress,
						  quint16 serverPort,
						  const QString & login,
						  const QString & password,
						  quint16 listeningPort,
						  const QString & token) {
	qDebug() << "Sending SREQ";
	hostAddress.setAddress(serverAddress);
	hostPort = serverPort;
	this->listeningPort = listeningPort;

	socket.bind(listeningPort);

	QByteArray arr((login + ":" + password
					+ ":" + QString::number(listeningPort)
					+ (token.isEmpty() ? QString() : QString(":") + token)).toAscii());

	sendData(B_TYPE_SREQ, arr);
}


void BConnection::disconnectFromHost() {
	qDebug() << "Disconnecting";

	sendData(B_TYPE_CLOSE);

	socket.disconnectFromHost();

	hostAddress.setAddress("A-S-D-F");
	hostPort = 0;
	listeningPort = 0;
	sessid = 0;
}

QByteArray * BConnection::newTMPdatagram(unsigned char command, QByteArray & data) {
	BDatagram gram(sessid, clientType,
				   (quint32) QDateTime::currentDateTime().toTime_t(),
				   command, data);
	return gram.getAllData();
}


int BConnection::sendData(BDatagram &data) {
	QByteArray * datagram = data.getAllData();
	int status = socket.writeDatagram(*datagram, hostAddress, hostPort);
	delete datagram;
	return status;
}

int BConnection::sendData(unsigned char command, QByteArray & data) {
	QByteArray * tmpGram = newTMPdatagram(command, data);
	int status = socket.writeDatagram(*tmpGram, hostAddress, hostPort);
	delete tmpGram;
	return status;
}

int BConnection::sendData(unsigned char command) {
	QByteArray empty;
	return sendData(command, empty);
}

void BConnection::timerEvent(QTimerEvent * e) {
	if(isSessionAlive() && socket.waitForBytesWritten(1)) {
		qDebug() << "Sending CHECK";
		sendData(B_TYPE_CHECK);
//		QByteArray empty;
//		BDatagram dgramAck(sessid, clientType,
//						   (quint32) QDateTime::currentDateTime().toTime_t(),
//						   (unsigned char)B_TYPE_CHECK, empty);
//		QByteArray * datagram = dgramAck.getAllData();
//
//		socket.writeDatagram(*datagram, hostAddress, hostPort);
//		delete datagram;
	}
}

BDatagram * BConnection::getData() {
	if(socket.state() != QUdpSocket::BoundState
	   || !socket.hasPendingDatagrams()) {
		return NULL;
	}

	if(socket.waitForReadyRead(1)) {
		int size = socket.pendingDatagramSize();
		if(size > 0) {
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
						qDebug() << "Logged in. Got session ID: " << datagram->sessid;
						sessid = datagram->sessid;
						delete datagram;
						emit connected(sessid);
					} else {
						delete datagram;
						throw BConnectionException("Someone tried to inject different sessionid");
					}
					break;

  case B_TYPE_SDEN:
					sessid = 0;
					delete datagram;
					throw BConnectionException("Server disconnected.");
					break;

  case B_TYPE_ERROR:
					throw BConnectionException("ERROR", datagram);
					break;

	case B_TYPE_OBJECT:
			default:
					return datagram;
				}
			}
		}
	}
	return NULL;
}

bool BConnection::isSessionAlive() {
	return sessid != 0;
}
