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
	settings()
{
	ui->setupUi(this);

	readSettings();
	startTimer(2000);

	connect(&connection, SIGNAL(connected(quint32)), SLOT(serverConnected(quint32)));
}

ConfigDialog::~ConfigDialog()
{
	if(vin) {
		vin->safelyStop();
		delete vin;
	}
	saveSettings();
    delete ui;
}

void ConfigDialog::connectCamera() {
	disconnectCamera();
	try {
		vin = new VideoInput(25); // todo ustawianie framerate
		vin->addObserver(this);
		vin->start();
	} catch (char* & message) {
		qDebug() << message;
		QMessageBox::warning(this, "Bd", message);
		vin = NULL;
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

void ConfigDialog::on_checkBox_toggled(bool checked)
{
	if(checked) {
		connectCamera();
	} else {
		disconnectCamera();
	}
}

void ConfigDialog::retreiveFrame(QImage & image) {
	ImageDisplayer * tmp = this->ui->cameraPreview;
	//tmp->setMinimumWidth(image.width());
	//tmp->setMinimumHeight(image.height());
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

void ConfigDialog::on_connectButton_clicked()
{
	if(! connection.isSessionAlive()) {
		saveSettings();

		//ui->connectionGroupBox->setEnabled(false);
		QListIterator<QObject*> children(ui->connectionGroupBox->children());
		while(children.hasNext()) {
			QObject* ob = children.next();
			if(ob->property("objectName").toString() != QString("connectButton")) {
				//ob->setProperty("enabled", false);
			}
		}

		ui->connectButton->setText("Anuluj laczenie");
		ui->connectButton->setEnabled(true);

		connection.connect(ui->addressEdit->text(),
						   (quint16) ui->serverPortBox->value(),
						   ui->loginEdit->text(),
						   ui->passwordEdit->text(),
						   (quint16) ui->localPortBox->value(),
						   ui->tokenEdit->text());
	}
}

void ConfigDialog::serverConnected(quint32 sessid) {
	qDebug() << "SERVER CONNECTED" << sessid;
}

void ConfigDialog::serverDisconnected() {
}

void ConfigDialog::timerEvent(QTimerEvent *event) {
	BDatagram * datagram = NULL;
	try {
		datagram = connection.getData();

		if(datagram) {
			qDebug() << "DATAGRAM" << datagram->getAllData();
			delete datagram;
		}
	} catch (BConnectionException &e) {
		qDebug() << e.toString();
		datagram = e.getDatagram();

		if(datagram) {
			qDebug() << "DATAGRAM" << datagram->getAllData();
		}
		// e zostanie delete, wiec datagram tez
	}

}


void ConfigDialog::readSettings() {
	ui->loginEdit->setText(settings.value("user/login", "cat").toString());
	ui->tokenEdit->setText(settings.value("user/token", "dog").toString());
	ui->localPortBox->setValue(settings.value("user/port", 1501).toInt());

	ui->addressEdit->setText(settings.value("sever/address", "127.0.0.1").toString());
	ui->serverPortBox->setValue(settings.value("server/port", 1500).toInt());

	bool savePassword = settings.value("user/save_password", false).toBool();
	ui->savePasswordCheck->setChecked(savePassword);

	if(savePassword) {
		ui->passwordEdit->setText(settings.value("user/password", "").toString());
	} else {
		settings.setValue("user/save_password", false);
	}
}

void ConfigDialog::saveSettings() {
	settings.setValue("user/login", ui->loginEdit->text());
	settings.setValue("user/token", ui->tokenEdit->text());
	settings.setValue("user/port", ui->localPortBox->value());
	settings.setValue("server/address", ui->addressEdit->text());
	settings.setValue("server/port", ui->serverPortBox->value());

	bool savePassword = ui->savePasswordCheck->isChecked();
	settings.setValue("user/save_password", savePassword);

	if(savePassword) {
		settings.setValue("user/password", ui->passwordEdit->text());
	} else {
		settings.setValue("user/password", "");
	}

	settings.sync();
}
