#include <QtGui/QApplication>
//#include <boblist.h>
//#include <QByteArray>
//#include <QDebug>
#include "idiotwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setOrganizationName("Buzztva");
	a.setApplicationName("Idiotic Client");
	a.setApplicationVersion("0.1");

	//bobsTest();

    IdiotWindow w;
    w.show();
    return a.exec();
}

//void bobsTest() {
//	BObList bobs;
//	for(quint16 i = 0; i < 640; ++i) {
//		bobs.append(BOb(i,i,i,i));
//	}
//
//	qDebug() << bobs.toString();
//	QByteArray * arr = bobs.pack();
//	BObList * bobs2 = new BObList(*arr);
//	qDebug() << bobs2->toString();
//	delete arr;
//	delete bobs2;
//}
