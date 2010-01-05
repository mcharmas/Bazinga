#include "frameretreiver.h"
#include "videoinput.h"

FrameRetreiver::FrameRetreiver(VideoInput * input) : input(input)
{
	if(input) input->addObserver(this);
}

FrameRetreiver::~FrameRetreiver() {
	if(input) input->delObserver(this);
}

void FrameRetreiver::setInput(VideoInput * input) {
	if(this->input) this->input->delObserver(this);
	this->input = input;
	if(input) input->addObserver(this);
}

void FrameRetreiver::retreiveFrame(cv::Mat & mat) {}

void FrameRetreiver::retreiveFrame(QImage & mat) {}
