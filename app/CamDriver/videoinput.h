#ifndef VIDEOINPUT_H
#define VIDEOINPUT_H

#include <QThread>
#include <QMutex>
#include <QList>
#include <QImage>

#include <opencv/cv.h>
#include <opencv/highgui.h>

class FrameRetreiver;

class VideoInput : public QThread
{
	Q_OBJECT
public:
	VideoInput(int frameRate);
	virtual ~VideoInput();
	void addObserver(FrameRetreiver *);
	void delObserver(FrameRetreiver *);
	void setFrameRate(float frameRate);
	float getFrameRate();
	unsigned long getSleepUTime();

public slots:
	void safelyStop();

protected:
	virtual void run();

private:
	void getFrame();

	cv::VideoCapture vid;
	cv::Mat frame;
	QImage image;

	QList<FrameRetreiver*> observers;
	QMutex observersMutex, frameRateMutex;
	float frameRate;
	unsigned long sleepUTime;
	bool running;
};

#endif // VIDEOINPUT_H
