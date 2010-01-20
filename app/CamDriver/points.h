#ifndef POINTS_H
#define POINTS_H

#include "frameretreiver.h"

class Points2 : public FrameRetreiver
{
private:

public:
    Points2(VideoInput* input);
    virtual ~Points2();
    void retreiveFrame(cv::Mat &);

private:
    int count;
    int max_count;
    int add_remove_pt;
    double quality;
    double min_distance;
    char *status;
    int flags;

    CvSize currBuffsSize;
    CvPoint2D32f* points[2], *swap_points;
    CvPoint pt;

    IplImage *tempImage;
    IplImage *currGreyImage;
    IplImage *prevGreyImage;
    IplImage *currPyramid;
    IplImage *prevPyramid;
    IplImage *swapImage;

    void checkSize(CvSize);
};

#endif // POINTS_H
