#include "imagedisplayer.h"
#include "points.h"
#include <QPainter>

void ImageDisplayer::commonSetup() {
	this->setAttribute(Qt::WA_OpaquePaintEvent, true);
	//this->startTimer(40);
}

ImageDisplayer::ImageDisplayer() : image(0)
{
	commonSetup();
}

ImageDisplayer::ImageDisplayer(QGroupBox*& a) : QWidget(a), image(0) {
	commonSetup();
}

void ImageDisplayer::setImage(QImage * image) {
	this->image = image;
}

void ImageDisplayer::mouseReleaseEvent(QMouseEvent *e)
{
    Points2::addPoint(e->pos().x(), e->pos().y());
}

void ImageDisplayer::paintEvent(QPaintEvent * e) {
	if(image) {
		if (this->width() < image->width() || this->height() < image->height()) {
			this->setMinimumSize(image->size());
			this->setMaximumSize(image->size());
		}

		QPainter paint(this);
		paint.drawImage(e->rect(), *image);
	}
}

void ImageDisplayer::timerEvent(QTimerEvent * e) {
	//this->update();
}
