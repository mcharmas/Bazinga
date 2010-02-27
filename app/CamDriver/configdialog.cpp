#include "configdialog.h"
#include "ui_configdialog.h"

#include <bconnectionexception.h>

#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>

ConfigDialog::ConfigDialog(QWidget *parent)
	: QDialog(parent),
	FrameRetreiver(NULL),
	ui(new Ui::ConfigDialog),
	vin(NULL),
	faceDetector(NULL),
	quadranglesDetector(NULL),
	pointsDetector(NULL),
	connection(B_SOURCE_DRIVER),
	settings(),
	cameraBlocker(this),
	connectionWidget(this, &connection, &settings, false, &cameraBlocker)
{
	ui->setupUi(this);

	ui->horizontalLayout->addWidget(&connectionWidget);

	//readSettings();
	startTimer(2000);

	connect(&connection, SIGNAL(connected(quint32)), SLOT(serverConnected(quint32)));

	connect(&connectionWidget, SIGNAL(throwException(BConnectionException*)), SLOT(catchException(BConnectionException*)));
}

ConfigDialog::~ConfigDialog()
{
	connection.disconnectFromHost();
	if(vin) {
		vin->safelyStop();
		delete vin;
	}
	saveSettings();
    delete ui;
}

void ConfigDialog::connectCamera() {
	//disconnectCamera();
	if(!vin) {
		vin = new VideoInput(25); // todo ustawianie framerate
		vin->addObserver(this);
		vin->start();
	}
}

void ConfigDialog::disconnectCamera() {
	this->ui->cameraPreview->setImage(NULL);
	if(vin) {
		vin->safelyStop();
		delete vin;
	}
	vin = NULL;
}

void ConfigDialog::catchException(BConnectionException * e) {
	QMessageBox::warning(this, QString("Zlapano wyjatek"), e->toString());
}

void ConfigDialog::on_connectCameraBox_toggled(bool checked)
{
	if(checked) {
		try {
			connectCamera();
		} catch (QString * message) {
			QMessageBox::warning(this, "Blad", *message);
			ui->connectCameraBox->setChecked(false);
			delete message;
		}
	} else {
		disconnectCamera();
	}
}

void ConfigDialog::retreiveFrame(QImage & image) {
	ImageDisplayer * tmp = this->ui->cameraPreview;
	tmp->setImage(&image);
	tmp->update();
}

void ConfigDialog::on_facesCheckBox_toggled(bool checked)
{
	if(vin) {
		if(checked) {
			vin->addObserver(&faceDetector);
		} else {
			vin->delObserver(&faceDetector);
		}
	}
}

void ConfigDialog::on_quadrangleCheckBox_toggled(bool checked)
{
    if(vin) {
		if(checked) {
			vin->addObserver(&quadranglesDetector);
		} else {
			vin->delObserver(&quadranglesDetector);
		}
    }
}

void ConfigDialog::on_pointsCheckBox_toggled(bool checked)
{
    if(vin) {
		if(checked) {
			vin->addObserver(&pointsDetector);
		} else {
			vin->delObserver(&pointsDetector);
		}
    }

}

void ConfigDialog::serverConnected(quint32 sessid) {
	qDebug() << "SERVER CONNECTED" << sessid;
}

void ConfigDialog::serverDisconnected() {
	qDebug() << "SERVER DISconnected";
}

void ConfigDialog::timerEvent(QTimerEvent *event) {
	BDatagram * datagram = NULL;
	try {
		datagram = connection.getData();

		if(datagram) {
			qDebug() << "DATAGRAM" << datagram->getAllData();
			delete datagram;
		}
	} catch (BConnectionException *e) {
		qDebug() << e->toString();
		datagram = e->getDatagram();

		if(datagram) {
			qDebug() << "DATAGRAM" << datagram->getAllData();
		}
		delete e;
	}

}


void ConfigDialog::readSettings() {
}

void ConfigDialog::saveSettings() {

	settings.sync();
}

