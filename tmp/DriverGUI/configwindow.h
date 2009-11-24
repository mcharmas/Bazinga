#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QtGui/QWidget>

namespace Ui {
    class ConfigWindow;
}

class ConfigWindow : public QWidget {
    Q_OBJECT
public:
    ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConfigWindow *m_ui;
};

#endif // CONFIGWINDOW_H
