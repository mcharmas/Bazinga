#include "videoinput.h"
#include "frameretreiver.h"
using namespace cv;

VideoInput::VideoInput(int frameRate) : vid(0), frameRate(frameRate), running(true), buffer(NULL)
{
	vid >> frame;
	if(frame.cols != image.width() || frame.rows != image.height()) {
		image = QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
	}
	//frame.data = image.bits();
	setFrameRate(frameRate);
	//namedWindow("ASDF",0);
}

VideoInput::~VideoInput() {}

void VideoInput::run() {
	while(running) {
		getFrame();

		observersMutex.lock();
		QList<FrameRetreiver*> observersCopy(observers);
		observersMutex.unlock();

		for(QList<FrameRetreiver*>::const_iterator it = observersCopy.constBegin();
		it != observersCopy.constEnd(); ++it) {
			(*it)->retreiveFrame(image);
			(*it)->retreiveFrame(frame);
		}

		this->usleep(getFrameRate());
	}
}

void VideoInput::getFrame() {
	vid >> frame;
	cvtColor(frame, frame, CV_BGR2RGB);
}

void VideoInput::safelyStop() {
	running = false;
	this->wait();
}

void VideoInput::setFrameRate(float frameRate) {
	frameRateMutex.lock();
	if(frameRate < 0) frameRate = -frameRate;
	if(frameRate == 0) return; // TODO: throw ?
	this->frameRate = frameRate;
	sleepUTime = (float) (1000000.0 / frameRate);
	frameRateMutex.unlock();
}

float VideoInput::getFrameRate() {
	frameRateMutex.lock();
	float tmp = this->frameRate;
	frameRateMutex.unlock();
	return tmp;
}

unsigned long VideoInput::getSleepUTime() {
	frameRateMutex.lock();
	unsigned long tmp = this->sleepUTime;
	frameRateMutex.unlock();
	return tmp;
}

void VideoInput::addObserver(FrameRetreiver * ft) {
	observersMutex.lock();
	observers.append(ft);
	observersMutex.unlock();
}

void VideoInput::delObserver(FrameRetreiver *ft) {
	observersMutex.lock();
	observers.removeOne(ft);
	observersMutex.unlock();
}
