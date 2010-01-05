#ifndef FACES_H
#define FACES_H

#include "frameretreiver.h"
#include <vector>

class Faces : public FrameRetreiver
{
public:
	Faces(VideoInput* input);
	void retreiveFrame(cv::Mat &);
private:
	cv::CascadeClassifier haar;

	std::vector<cv::Rect> objects;

};

#endif // FACES_H
