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
#include "quadrangles.h"
#include "points.h"

namespace Ui
{
	class ConfigDialog;
}

class ConfigDialog : public QDialog, public FrameRetreiver
{
	Q_OBJECT

public:

	friend bool CameraNotConnectedBlocker::canConnect();

	ConfigDialog(QWidget *parent = 0);
	~ConfigDialog();

public slots:
	void connectCamera();
	void disconnectCamera();

	void serverConnected(quint32 sessid);
	void serverDisconnected();

	void saveSettings();
	void readSettings();

	void catchException(BConnectionException * e);

private:
	void retreiveFrame(QImage & image);
	void timerEvent(QTimerEvent * event);

	Ui::ConfigDialog *ui;
	VideoInput * vin;
	Faces faceDetector;
	Quadrangles quadranglesDetector;
	Points2 pointsDetector;
	BConnection connection;
	QSettings settings;
	CameraNotConnectedBlocker cameraBlocker;
	BConnectionWidget connectionWidget;

private slots:
	void on_connectCameraBox_toggled(bool checked);
	void on_pointsCheckBox_toggled(bool checked);
	void on_quadrangleCheckBox_toggled(bool checked);
	void on_facesCheckBox_toggled(bool checked);
};

#endif // CONFIGDIALOG_H
