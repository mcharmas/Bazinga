#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPen>
#include <boblist.h>

class ImageWidget : public QWidget
{
Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);

	BObList bobs;
	QPen pen;
protected:
	void paintEvent(QPaintEvent *ev);
};

#endif // IMAGEWIDGET_H
