#ifndef QUADRANGLES_H
#define QUADRANGLES_H

#include "frameretreiver.h"

class Quadrangles : public FrameRetreiver
{
private:
    double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 );

public:
    Quadrangles(VideoInput* input);
    void retreiveFrame(cv::Mat &);
};

#endif // QUADRANGLES_H
