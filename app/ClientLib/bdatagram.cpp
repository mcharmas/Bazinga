#include "bdatagram.h"

BDatagram::BDatagram(quint32 sessid, unsigned char source, quint32 timestamp, unsigned char type, QByteArray & data)
	: sessid(sessid),
	source(source),
	timestamp(timestamp),
	type(type),
	data(data)
{
}

BDatagram::BDatagram(char *dataIn, int size) {
	sessid = *((quint32*)dataIn);
	dataIn += 4;

	source = *dataIn;
	dataIn++;

	timestamp = *((quint32*)dataIn);
	dataIn += 4;


	type = *dataIn;
	dataIn++;

	dataIn += 2; // pomijanie rozmiaru TODO: moze sprawdzac, czy rozmiar danych sie zgadza z size - 12 (rozmiar naglowka)

	data.append(dataIn, size - 12);
}

QByteArray * BDatagram::getAllData() {
	QByteArray * tmp = new QByteArray();
	tmp->append((char*) &sessid, 4);
	tmp->append(source);
	tmp->append((char*) &timestamp, 4);
	tmp->append(type);
	tmp->append((quint16) data.size());
	tmp->append(data);
	return tmp;
}

