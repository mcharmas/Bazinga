#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtGui/QDialog>
#include <QSettings>

#include <bconnection.h>

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
	ConfigDialog(QWidget *parent = 0);
	~ConfigDialog();

public slots:
	void connectCamera();
	void disconnectCamera();

	void saveSettings();
	void readSettings();

private:
	void retreiveFrame(QImage &);

	Ui::ConfigDialog *ui;
	VideoInput * vin;
	Faces faceDetector;
	Quadrangles quadranglesDetector;
	Points2 pointsDetector;
	BConnection connection;
	QSettings settings;


private slots:
	void on_connectButton_clicked();
	void on_pointsCheckBox_toggled(bool checked);
	void on_quadrangleCheckBox_toggled(bool checked);
	void on_facesCheckBox_toggled(bool checked);
	void on_checkBox_toggled(bool checked);
};

#endif // CONFIGDIALOG_H
