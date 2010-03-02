#include "bconnectionwidget.h"
#include "bconnectionexception.h"
#include "ui_bconnectionwidget.h"

BConnectionWidget::BConnectionWidget(QWidget *parent, BConnection *connection,
									 QSettings *settings, bool useToken,
									 BConnectionBlocker *blocker) :
    QWidget(parent),
	ui(new Ui::BConnectionWidget),
	connection(NULL),
	settings(settings),
	blocker(blocker),
	useToken(false),
	attemptingToConnect(false)
{
    ui->setupUi(this);
	setConnectionObject(connection);
	setUseToken(useToken);
	readSettings();
}

BConnectionWidget::~BConnectionWidget()
{
	saveSettings();
    delete ui;
}

void BConnectionWidget::on_savePasswordCheck_toggled(bool checked)
{}

void BConnectionWidget::readSettings() {
	if(settings) {
		ui->loginEdit->setText(settings->value("user/login", "cat").toString());
		ui->localPortBox->setValue(settings->value("user/port", 1501).toInt());

		if(useToken) {
			ui->tokenEdit->setText(settings->value("user/token", "dog").toString());
		}

		ui->addressEdit->setText(settings->value("sever/address", "127.0.0.1").toString());
		ui->serverPortBox->setValue(settings->value("server/port", 1500).toInt());

		bool savePassword = settings->value("user/save_password", false).toBool();
		ui->savePasswordCheck->setChecked(savePassword);

		if(savePassword) {
			ui->passwordEdit->setText(settings->value("user/password", "").toString());
		} else {
			settings->setValue("user/save_password", false);
		}
	}
}

void BConnectionWidget::saveSettings() {
	if(settings) {
		settings->setValue("user/login", ui->loginEdit->text());
		settings->setValue("user/port", ui->localPortBox->value());

		settings->setValue("user/token",
						   useToken ? ui->tokenEdit->text() : QString());

		settings->setValue("server/address", ui->addressEdit->text());
		settings->setValue("server/port", ui->serverPortBox->value());

		bool savePassword = ui->savePasswordCheck->isChecked();
		settings->setValue("user/save_password", savePassword);

		if(savePassword) {
			settings->setValue("user/password", ui->passwordEdit->text());
		} else {
			settings->setValue("user/password", "");
		}

		settings->sync();
	}
}

void BConnectionWidget::on_connectButton_clicked()
{
	emit connectButtonClicked();
	try {
		if(connection) {
			if(! connection->isSessionAlive() && ! attemptingToConnect) {

				if(blocker && ! blocker->canConnect())
					throw new BConnectionException(QString("Blocker blocked connecting: ") + blocker->toString());

				saveSettings();
				attemptingToConnect = true;

				ui->connectButton->setText("Anuluj laczenie");
				setConnectionGroupBoxEnabled(false);

				connection->connect(ui->addressEdit->text(),
									(quint16) ui->serverPortBox->value(),
									ui->loginEdit->text(),
									ui->passwordEdit->text(),
									(quint16) ui->localPortBox->value(),
									ui->tokenEdit->text());
			} else {
				if(blocker && ! blocker->canDisconnect())
					throw new BConnectionException("Blocker blocked disconnecting: " + blocker->toString());

				connection->disconnectFromHost();
				ui->connectButton->setText("Polacz");
				setConnectionGroupBoxEnabled(true);
				attemptingToConnect = false;
			}
		}
	} catch (BConnectionException* e) {
		emit throwException(e);
		delete e;
	}
}

void BConnectionWidget::serverConnected(quint32 sessid)
{
	ui->connectButton->setText("Rozlacz");
	attemptingToConnect = false;
}

void BConnectionWidget::serverDisconnected()
{
	ui->connectButton->setText("Polacz");
	setConnectionGroupBoxEnabled(true);
	attemptingToConnect = false;
}

void BConnectionWidget::setConnectionGroupBoxEnabled(bool enabled, bool connectButtonEnabled)
{
	QListIterator<QObject*> children(ui->connectionGroupBox->children());
	while(children.hasNext()) {
		QObject* ob = children.next();
		ob->setProperty("enabled", enabled);
	}

	ui->connectButton->setEnabled(connectButtonEnabled);
}

void BConnectionWidget::pushConnectButton() {
	ui->connectButton->click();
}

/********************************************
  DULL STUFF = SETTERS, ETC
  ******************************************/

void BConnectionWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void BConnectionWidget::setConnectionObject(BConnection * connection) {
	this->connection = connection;
	bool panelEnabled = (connection != NULL);

	setConnectionGroupBoxEnabled(panelEnabled, panelEnabled);

	if(panelEnabled) {
		connect(connection, SIGNAL(connected(quint32)), SLOT(serverConnected(quint32)));
		connect(connection, SIGNAL(disconnected()), SLOT(serverDisconnected()));
	}
}

void BConnectionWidget::setSettingsObject(QSettings *settings)
{
	this->settings = settings;
	readSettings();
}

void BConnectionWidget::setBlockerObject(BConnectionBlocker *blocker)
{
	this->blocker = blocker;
}

void BConnectionWidget::setUseToken(bool use) {
	useToken = use;
	ui->tokenEdit->setVisible(use);
	ui->tokenLabel->setVisible(use);
	ui->connectionGroupBox->layout()->update();
}


