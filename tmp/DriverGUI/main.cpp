#include <QtGui/QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include "configwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	ConfigWindow window;
	QMenu menu;
	QSystemTrayIcon trayIcon;
	if( ! QSystemTrayIcon::isSystemTrayAvailable()) {
		window.show();
	} else {
		menu.addAction("Konfiguracja", &window, SLOT(show()));
		menu.addAction("Zakoncz", &a, SLOT(quit()));
		trayIcon.setContextMenu(&menu);
		trayIcon.show();
	}
    return a.exec();
}
