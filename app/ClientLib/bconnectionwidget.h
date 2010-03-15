#ifndef BCONNECTIONWIDGET_H
#define BCONNECTIONWIDGET_H

#include "ClientLib_global.h"
#include "bconnection.h"
#include "bconnectionblocker.h"
#include "bconnectionexception.h"

#include <QWidget>
#include <QSettings>

namespace Ui {
    class BConnectionWidget;
}

/*! \brief Widget z wszystkimi polami potrzebnymi do logowania

  \li Widget moze zapisac ustawienia w obiekcie typu QSettings, jesli podano.
  \li Moze sie odwolywac do obiektu powstrzymujacego logowanie typu BConnectionBlocker.
  */
class CLIENTLIBSHARED_EXPORT BConnectionWidget : public QWidget {
    Q_OBJECT
public:

	/*! \brief konstruktor

	  \sa setSettingsObject(QSettings * settings), setBlockerObject(BConnectionBlocker * blocker), setUseToken(bool use)
	  */
	BConnectionWidget(QWidget *parent = 0, //!< widget-rodzic
					  BConnection * connection = NULL, //!< obiekt polaczenia, bardzo potrzebny IMHO ;)
					  QSettings * settings = NULL, //!< Jesli podano, ustawienia zostana odczytane i zapisane z/do tego obiektu.
					  bool useToken = true, //!< Uzywaj pola token, wylaczenie spowoduje znikniecie pola tokenu z formularza
					  BConnectionBlocker * blocker = NULL /*!< Ustaw obiekt blokujacy */);
    ~BConnectionWidget();

	/*! \brief Ustaw obiekt do skladowania ustawien.

	  W podanym obiekcie zostana zapisane ustawienia logowania w odpowiednich kluczach:
	  \li user/login
	  \li user/save_password - true/false
	  \li user/password - jesli zaznaczono zapisywanie hasla
	  \li user/token - jesli useToken
	  \li user/port - lokalny port do nasluchiwania
	  \li server/address
	  \li server/port

	  Pierwszy odczyt ustawien odbywa sie w wywolaniu tej funkcji

	  Zapisywanie odbywa sie przy kazdej probie nawiazania polaczenia.
	  */
	void setSettingsObject(QSettings * settings);

	/*! \brief Ustaw obiekt blokujacy.

	  Obiekt blokujacy jest odpytywany przed proba polaczenia
	( BConnectionBlocker::canConnect() ) i rozlaczenia
 (BConnectionBlocker::canDisconnect() ) czy mozna nawiazywac polaczenie.

 Moze to byc przydatne dla uzytkownika tej klasy, jesli chce okreslic swoje
 warunki nawiazania/przerwania polaczenia.
 */
	void setBlockerObject(BConnectionBlocker * blocker);

	/*! \brief Ustaw obiekt polaczenia.

	  Bez tego nie ma za bardzo sensu uzycie tej klasy.

	  Widget sam sobie ustawia polaczenia do BConnection::connected(quint32 sessid)
	do serverConnected(quint32 sessid)) i analogicznie BConnection::disconnected()
	do serverDisconnected().
	  */
	void setConnectionObject(BConnection * connection);

	/*! \brief Uzywaj pola na token albo nie.

	  Jesli use, pokaz pole na token. Spowoduje rowniez to, ze token nie bedzie
	  zapisny w ustawieniach.
	  */
	void setUseToken(bool use);

public slots:
	/*! \brief Informuj o nawiazaniu polaczenia.

	  Widget sam dba o odpowienie podpiecie tu sygnalu z obiektu polaczenia.
	  */
	void serverConnected(quint32 sessid);
	/*! \brief Informuj o rozlaczeniu

	  \sa serverConnected(quint32 sessid);
	  */
	void serverDisconnected();

	/*! \brief Programowo przydus przycisk polaczenia.
	  */
	void pushConnectButton();

	//! \brief zapisz ustawienia
	void saveSettings();

	//! \brief odczytaj ustawienia
	void readSettings();


signals:
	/*! \brief Emitowany zaraz po wcisniecu przycisku polaczenia.

	  Na wszelki przypadek, gdyby programista chcial wiedziec, kiedy uzytkownik
	  wciska przycisk.

	  Emitowane tuz po wcisniecu polaczenia i jeszcze przed podjeciem akcji polaczenia/rozlaczenia/rezygnacji z proby nawiazania polaczenia.
	  */
	void connectButtonClicked();

	/*! \brief Sygnal, ktory jest emitowany, jesli wewnatrz zostanie wykryty jakis
	  wyjatek.

	  Przydatne do wylapywania wyjatkow przez programiste uzywajacego tej klasy.

	\warning Nie kasuj rzucanego obiektu na wlasna reke. Zostanie on
	  skasowany po obsludze przez wszystkich obiorcow tego sygnalu.
	  */
	void throwException(BConnectionException*);

protected:
	/*! \brief wygenerowane przez QtDesignera

	  Chyba chodzi o dynamiczna zmiane jezyka
	  */
    void changeEvent(QEvent *e);

private:

	//! \brief uzywane wewnetrznie do wylaczania pol
	void setConnectionGroupBoxEnabled(bool enabled, bool connectButtonEnabled = true);

private:
	//! \brief obiekt z UI
    Ui::BConnectionWidget *ui;
	//! obiekt polaczenia
	BConnection * connection;
	//! obiekt ustawien
	QSettings * settings;
	//! obikt blokujacy nawiazywanie polaczenia
	BConnectionBlocker  * blocker;
	//! uzywak tokena albo nie.
	bool useToken;
	//! informuje czy jestesmy na etapie nawiazywania polaczenia czy nie.
	bool attemptingToConnect;

private slots:
	//! walnieto w przycisk polaczenia/rozlaczenia.
	void on_connectButton_clicked();
	//! zmieniono stan przycisku do zapisywania hasla.
 void on_savePasswordCheck_toggled(bool checked);
};

#endif // BCONNECTIONWIDGET_H
