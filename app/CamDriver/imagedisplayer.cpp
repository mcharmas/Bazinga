#include "imagedisplayer.h"
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

void ImageDisplayer::paintEvent(QPaintEvent * e) {
	if(image) {
		this->setMinimumSize(image->size());
		QPainter paint(this);
		paint.drawImage(e->rect(), *image);
	}
}

void ImageDisplayer::timerEvent(QTimerEvent * e) {
	//this->update();
}
