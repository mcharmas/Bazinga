#include "imagewidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QListIterator>
#include <QMapIterator>


ImageWidget::ImageWidget(QWidget *parent) :
	QWidget(parent)
{
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(3);
	pen.setBrush(Qt::SolidPattern);
	colorNames = QColor::colorNames();
}

ImageWidget::~ImageWidget() {
	QMapIterator<quint32, BObList*> it(boblists);
	while(it.hasNext()) {
		it.next();
		if(it.value()) delete it.value();
	}
}

void ImageWidget::setBObs(quint32 sessid, BObList *list) {
	BObList * old = boblists[sessid];
	if(old) delete old;
	if(list) {
		boblists[sessid] = list;
	} else {
		boblists.remove(sessid);
	}
}

void ImageWidget::paintEvent(QPaintEvent *ev) {
	QPainter paint(this);

	QMapIterator<quint32, BObList*> listIt(boblists);
	while (listIt.hasNext()) {
		listIt.next();
		BObList * v = listIt.value();
		if(v) {
			pen.setColor(QColor(colorNames[listIt.key() % colorNames.size()]));
			paint.setPen(pen);

			QListIterator<BOb> it(*v);
			while(it.hasNext()) {
				BOb tmp(it.next());
				if (!tmp.width || !tmp.height) {
					tmp.width ++;
					tmp.height++;
				}

				paint.drawRect(tmp.x, tmp.y, tmp.width, tmp.height);
			}
		}
	}
}
