#ifndef FRAMERETREIVER_H
#define FRAMERETREIVER_H

//#include <QObject>
#include <QImage>

#include <opencv/cv.h>

class VideoInput;

class FrameRetreiver
{
public:
	FrameRetreiver(VideoInput * input);
	void setInput(VideoInput * input);
	void getInput();

	virtual ~FrameRetreiver();

	virtual void retreiveFrame(QImage &);
	virtual void retreiveFrame(cv::Mat &);
private:
	VideoInput * input;
};

#endif // FRAMERETREIVER_H
