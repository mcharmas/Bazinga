#ifndef QUADRANGLES_H
#define QUADRANGLES_H

#include "frameretreiver.h"

class Quadrangles : public FrameRetreiver
{
public:
    Quadrangles(VideoInput* input);
    void retreiveFrame(cv::Mat &);
};

#endif // QUADRANGLES_H
