#include <QtGui/QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include "configdialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setOrganizationName("Buzztva");
	a.setApplicationName("Bazinga Driver");
	a.setApplicationVersion("0.1");

	// TODO: tymczasowo ustawione na true, zmienic na false:
	a.setQuitOnLastWindowClosed(true);
	ConfigDialog w;

	QMenu menu;
	QSystemTrayIcon trayIcon(QIcon(":/tray/icon.png"));
	if( QSystemTrayIcon::isSystemTrayAvailable()) {
		menu.addAction("Konfiguracja", &w, SLOT(show()));
		menu.addAction("Zakoncz", &a, SLOT(quit()));
		QObject::connect(&trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), &w, SLOT(show()));
		trayIcon.setContextMenu(&menu);
		trayIcon.show();
	} else {
		w.show();
	}

	// TODO: tymczasowo:
	w.show();
	//

	return a.exec();
}
