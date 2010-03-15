#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtGui/QDialog>
#include <QSettings>

#include <bconnection.h>
#include <bconnectionblocker.h>
#include <bconnectionwidget.h>
#include <boblist.h>

#include "cameranotconnectedblocker.h"
#include "frameretreiver.h"
#include "videoinput.h"
#include "faces.h"
#include "points.h"

namespace Ui
{
	class ConfigDialog;
}

/*! \brief Klasa wyświetlająca okno konfiguracyjne
	*/
class ConfigDialog : public QDialog, public FrameRetreiver
{
	Q_OBJECT

public:

	/*! Pozwala na dostęp do tego obiektu z metody sprawdzającej
	czy jest podłączona kamerka. */
	friend bool CameraNotConnectedBlocker::canConnect();

	/*! \brief Konstruktor

	  Ustawia connecty m/obiektami i włącza timer (2s) */
	ConfigDialog(QWidget *parent = 0);

	/*! \brief Destruktor

	  Próbuje rozłączyć kamerę i połączenie.
	  Zapisuje ustawienia */
	~ConfigDialog();

public slots:
	/*! \brief Podłącza kamerę */
	void connectCamera();

	/*! \brief Rozłącza kamerę */
	void disconnectCamera();

	/*! \brief Wywołaj, żeby poinformować okno o nawiązaniu połączenia

	  Już podłączone w konstruktorze */
	void serverConnected(quint32 sessid);

	/*! \brief Wywołaj, żeby poinformować okno o rozwiązaniu połączenia

	  Już podłączone w konstruktorze */
	void serverDisconnected();

	/*! \brief Zapisz ustawienia

	  Zapisywane w destruktorze */
	void saveSettings();

	/*! \brief Odczytaj ustawienia */
	void readSettings();

	/*! \brief Wyświetl komunikat z treścią wyjątku */
	void catchException(BConnectionException * e);

private:
	void retreiveFrame(QImage & image);
	void timerEvent(QTimerEvent * event);

	Ui::ConfigDialog *ui;
	VideoInput * vin;
	Faces faceDetector;
	Points2 pointsDetector;
	BConnection connection;
	QSettings settings;
	CameraNotConnectedBlocker cameraBlocker;
	BConnectionWidget connectionWidget;

private slots:
	void on_connectCameraBox_toggled(bool checked);
	void on_pointsCheckBox_toggled(bool checked);
	void on_facesCheckBox_toggled(bool checked);
};

#endif // CONFIGDIALOG_H
