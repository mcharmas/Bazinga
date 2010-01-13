#include "configdialog.h"
#include "ui_configdialog.h"

#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>

ConfigDialog::ConfigDialog(QWidget *parent)
	: QDialog(parent), FrameRetreiver(NULL), ui(new Ui::ConfigDialog), vin(NULL), faceDetector(NULL)
{
    ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
	if(vin) {
		vin->safelyStop();
		delete vin;
	}
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
		QMessageBox::warning(this, "B��d", message);
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
