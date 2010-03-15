#include "idiotwindow.h"
#include "ui_idiotwindow.h"

IdiotWindow::IdiotWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::IdiotWindow),
	connection(B_SOURCE_APP)
{
    ui->setupUi(this);
	ui->connectionWidget->setSettingsObject(&settings);
	ui->connectionWidget->setConnectionObject(&connection);
	startTimer(10);
}

IdiotWindow::~IdiotWindow()
{
	connection.disconnectFromHost();
    delete ui;
}

void IdiotWindow::timerEvent(QTimerEvent *ev) {
	BDatagram * datagram = NULL;
	try {
		datagram = connection.getData();

		if(datagram) {
			BObList * bobjects = new BObList(datagram->data);
			ui->imageWidget->setBObs(datagram->sessid, bobjects);
			ui->imageWidget->update();
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

void IdiotWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

