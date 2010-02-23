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

class CLIENTLIBSHARED_EXPORT BConnectionWidget : public QWidget {
    Q_OBJECT
public:
	BConnectionWidget(QWidget *parent = 0,
					  BConnection * connection = NULL,
					  QSettings * settings = NULL,
					  bool useToken = true,
					  BConnectionBlocker * blocker = NULL);
    ~BConnectionWidget();

	void setSettingsObject(QSettings * settings);
	void setBlockerObject(BConnectionBlocker * blocker);
	void setConnectionObject(BConnection * connection);
	void setUseToken(bool use);

public slots:
	void serverConnected(quint32 sessid);
	void serverDisconnected();
	void pushConnectButton();

signals:
	void connectButtonClicked();

	/*! \brief Sygnal, ktory jest emitowany, jesli wewnatrz zostanie wykryty jakis
	  wyjatek.

	Sygnal, ktory jest emitowany, jesli wewnatrz zostanie wykryty jakis
	  wyjatek.

	\warning Nie kasuj rzucanego obiektu na wlasna reke. Zostanie on
	  skasowany po obsludze przez wszystkich tego sygnalu.
	  */
	void throwException(BConnectionException*);

protected:
    void changeEvent(QEvent *e);

private:
	void setConnectionGroupBoxEnabled(bool enabled, bool connectButtonEnabled = true);
	void saveSettings();
	void readSettings();

private:
    Ui::BConnectionWidget *ui;
	BConnection * connection;
	QSettings * settings;
	BConnectionBlocker  * blocker;
	bool useToken;
	bool attemptingToConnect;

private slots:
	void on_connectButton_clicked();
 void on_savePasswordCheck_toggled(bool checked);
};

#endif // BCONNECTIONWIDGET_H
