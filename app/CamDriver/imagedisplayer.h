#ifndef IMAGEDISPLAYER_H
#define IMAGEDISPLAYER_H

#include <QWidget>
#include <QImage>
#include <QPaintEvent>
#include <QGroupBox>

class ImageDisplayer : public QWidget
{
	Q_OBJECT
public:
    ImageDisplayer();
	ImageDisplayer(QGroupBox*&);
	void setImage(QImage * image);

protected:
	void paintEvent(QPaintEvent *);
	QImage * image;
};

#endif // IMAGEDISPLAYER_H
