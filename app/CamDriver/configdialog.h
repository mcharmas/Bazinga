#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtGui/QDialog>

#include "frameretreiver.h"
#include "videoinput.h"

namespace Ui
{
    class ConfigDialog;
}

class ConfigDialog : public QDialog, public FrameRetreiver
{
    Q_OBJECT

public:
    ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

public slots:
	void connectCamera();
	void disconnectCamera();

private:
	void retreiveFrame(QImage &);

    Ui::ConfigDialog *ui;
	VideoInput * vin;

private slots:
	void on_checkBox_toggled(bool checked);
};

#endif // CONFIGDIALOG_H
