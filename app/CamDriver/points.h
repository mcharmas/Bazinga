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
    static void addPoint( int, int);
    static CvPoint pt;
    static int add_remove_pt;

private:
    int count;
    int max_count;
//    int add_remove_pt;
    double quality;
    double min_distance;
    bool active;
    char *status;
    int flags;

    CvSize currBuffsSize;
    CvPoint2D32f* points[2], *swap_points;

    IplImage *tempImage;
    IplImage *currGreyImage;
    IplImage *prevGreyImage;
    IplImage *currPyramid;
    IplImage *prevPyramid;
    IplImage *swapImage;

    void checkSize(CvSize);
};

#endif // POINTS_H
