#include "imagedisplayer.h"
#include <QPainter>

ImageDisplayer::ImageDisplayer() : image(0)
{
}
ImageDisplayer::ImageDisplayer(QGroupBox*& a) : QWidget(a), image(0) {}

void ImageDisplayer::setImage(QImage * image) {
	this->image = image;
}

void ImageDisplayer::paintEvent(QPaintEvent * e) {
	if(image) {
		QPainter paint(this);
		paint.drawImage(e->rect(), *image);
	}
}
