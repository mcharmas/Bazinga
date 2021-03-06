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
	pointsDetector(NULL),
	connection(B_SOURCE_DRIVER),
	settings(),
	cameraBlocker(this),
	connectionWidget(this, &connection, &settings, false, &cameraBlocker)
{
	ui->setupUi(this);

	ui->horizontalLayout->addWidget(&connectionWidget);

	// qonnecty dla obiektu polaczenia
	connect(&connection, SIGNAL(connected(quint32)), SLOT(serverConnected(quint32)));

	// qonnecty dla widgetu polaczenia
	connect(&connectionWidget, SIGNAL(throwException(BConnectionException*)), SLOT(catchException(BConnectionException*)));

	// qonnecty dla obiektow emitujacych listy obiektow.
	connect(&faceDetector, SIGNAL(bobjects(BObList*)), &connection, SLOT(sendObjects(BObList*)));
	connect(&pointsDetector, SIGNAL(bobjects(BObList*)), &connection, SLOT(sendObjects(BObList*)));

	//readSettings();
	startTimer(2000);
}

ConfigDialog::~ConfigDialog()
{
	connection.disconnectFromHost();
	if(vin) {
		vin->safelyStop();
		delete vin;
	}
	connectionWidget.saveSettings();
    delete ui;
}

void ConfigDialog::connectCamera() {
	if(!vin) {
		vin = new VideoInput(25);
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

