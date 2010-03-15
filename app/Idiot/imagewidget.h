#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPen>
#include <QMap>
#include <QStringList>
#include <boblist.h>

class ImageWidget : public QWidget
{
Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);
	~ImageWidget();

	void setBObs(quint32 sessid, BObList * list);

protected:
	void paintEvent(QPaintEvent *ev);
	QMap<quint32, BObList*> boblists;
	QPen pen;
	QStringList colorNames;
};

#endif // IMAGEWIDGET_H
