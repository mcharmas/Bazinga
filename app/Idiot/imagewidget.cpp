#include "imagewidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QListIterator>


ImageWidget::ImageWidget(QWidget *parent) :
	QWidget(parent)
{
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(3);
	pen.setBrush(Qt::SolidPattern);
}

void ImageWidget::paintEvent(QPaintEvent *ev) {
	QPainter paint(this);
	paint.setPen(pen);
	QListIterator<BOb> it(bobs);
	while(it.hasNext()) {
		BOb tmp(it.next());
		if (!tmp.width || !tmp.height) {
			tmp.width ++;
			tmp.height++;
		}

		paint.drawRect(tmp.x, tmp.y, tmp.width, tmp.height);
	}
}
