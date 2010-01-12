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
	void timerEvent(QTimerEvent *);
	QImage * image;

private:
	void commonSetup();
};

#endif // IMAGEDISPLAYER_H
