#ifndef IDIOTWINDOW_H
#define IDIOTWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTimerEvent>
#include <bconnection.h>

namespace Ui {
    class IdiotWindow;
}

class IdiotWindow : public QMainWindow {
    Q_OBJECT
public:
    IdiotWindow(QWidget *parent = 0);
    ~IdiotWindow();

protected:
    void changeEvent(QEvent *e);
	void timerEvent(QTimerEvent *ev);

private:
    Ui::IdiotWindow *ui;
	BConnection connection;
	QSettings settings;
};

#endif // IDIOTWINDOW_H
