#include "configwindow.h"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ConfigWindow)
{
    m_ui->setupUi(this);
}

ConfigWindow::~ConfigWindow()
{
    delete m_ui;
}

void ConfigWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
