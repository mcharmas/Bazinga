#include "configdialog.h"
#include "ui_configdialog.h"

#include <QImage>
#include <QPainter>

ConfigDialog::ConfigDialog(QWidget *parent)
	: QDialog(parent), FrameRetreiver(NULL), ui(new Ui::ConfigDialog), vin(NULL)
{
    ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::connectCamera() {
	disconnectCamera();
	vin = new VideoInput(15); // todo ustawianie framerate
	vin->addObserver(this);
	vin->start();
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
	tmp->setMinimumWidth(image.width());
	tmp->setMinimumHeight(image.height());
	tmp->setImage(&image);
	tmp->update();
}

