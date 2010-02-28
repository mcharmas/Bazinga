#ifndef BCONNECTION_H
#define BCONNECTION_H

#include "ClientLib_global.h"

#include "bdatagram.h"

#include <QUdpSocket>
#include <QHostAddress>

/*! \brief Klasa reprezentujaca polaczenie.

  Obiekt po polaczeniu wysyla do serwera okresowo pakiet informujacy, ze jeszcze zyje.
  Odbieranie informacji wykonuje sie zawsze jawnie odpalajac getData().
  */
class CLIENTLIBSHARED_EXPORT BConnection : public QObject
{
	Q_OBJECT
public:

	/*! \brief Konstruuje obiekt z ustawionym typem klienta.
	  */
	BConnection(unsigned char clientType /*!< B_SOURCE_DRIVER albo B_SOURCE_APP */);

	/*! \brief Sprawda czy sesja jest aktywna

	  Technicznie sprowadza sie to do sprawdzenia czy sessid != 0.

	  \return true jesli sesja jest aktywna, false w przeciwnym przypadku.
	  */
	bool isSessionAlive();

	/*! \brief Laczy z serwerem

	  Binduje podany port (listeningPort), laczy sie z serwerem na podanym porcie, loguje na podstawie podanych danych (token moze byc pusty i nie podany)

	  Wysyla serwerowi komunikat SREQ o tresci login:haslo:port:token lub
	  login:haslo:port w zaleznosci od tego, czy token zostal podany.

		  \warning Nie czeka na potwierdzenie serwera. Trzeba wywolac getData(),
	wtedy, jesli zostanie odebrane od serwera potwierdzenie zalogowania,
	obiekt polaczenia wyemituje sygnal connected(quint32 sessid).
	  */
	void connect(const QString & serverAddress, //!< adres serwera
				 quint16 serverPort, //!< port serwera
				 const QString & login, //!< login
				 const QString & password, //!< haslo
				 quint16 listeningPort, //!< port na ktorym driver bedzie nasluchiwal potwierdzen z serwera
				 const QString & token = QString() /*!< token gry, parametr opcjonalny */);

	/*! \brief Rozlacz sie z serwerem.

	  Wysyla do serwera CLOSE i wylacza nasluchiwanie na porcie lokalnym.
	  */
	void disconnectFromHost();

	/*! \brief Wysyla przygotowany wczesniej datagram

	  \return status jak w QUDPSocket::writeDatagram();
	  */
	int sendData(BDatagram & data);

	/*! \brief Wysyla datagram z danymi.

	  Ustawia odpowiednio pole command i dane. Reszta jest pobierana z wlasciwosci
	  tego obiektu.

	  \return status jak w QUDPSocket::writeDatagram();
	  */
	int sendData(unsigned char command, QByteArray & data);

	/*! \brief Wysyla pusty datagram.

	  jak w sendData(unsigned char command, QByteArray & data)
	  tylko ze wysyla sam naglowek.

	  \return status jak w QUDPSocket::writeDatagram();
	  */
	int sendData(unsigned char command);

	/*!
	  \brief Odbierz datagram od serwera.

	  Metoda wstepnie przetwarza pobrany pakiet. W zaleznosci od jego zawartosci
	  moze:
	  \li zwrocic datagram.
	  \li rzucic wyjatkiem BConnectionException z zawartoscia pakietu badz nie.
	  \li zapisac sobie id sesji, wyemitowac sygnal connected(quint32 sessid) i zwrocic NULL. Od tego momentu zakladane jest, ze polaczenie zostalo nawiazane.
	  */
	BDatagram * getData();

signals:
	/*! \brief Emitowany, gdy serwer wysle info o polaczeniu. */
	void connected(quint32 sessid /*!< id sesji */);

	/*! \brief Emitowany, gdy serwer wysle informacje o zerwaniu polaczenia. */
	void disconnected();

private:
	/*! \brief Wysylanie co jakis czas CHECK do serwera.

	  Interwal okreslony jest w B_INTERVAL_ACK_MS.
	  Wysylane tylko, gdy isSessionAlive().
	  Timer uruchamiany jest w konstruktorze.
	  */
	void timerEvent(QTimerEvent *);

	/*! \brief uzywana wewnetrzenie do generowania datagramow. */
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
