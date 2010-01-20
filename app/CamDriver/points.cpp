#include "points.h"

Points2::Points2(VideoInput *input) : FrameRetreiver(input), count(0), max_count(50), add_remove_pt(0), quality(0.01), min_distance(10)
{
        currBuffsSize.width = 0;
        currBuffsSize.height = 0;
        pt.x = 120;

        pt.y = 160;
        add_remove_pt = 1;
        points[0] = (CvPoint2D32f*)cvAlloc(max_count*sizeof(points[0][0]));
        points[1] = (CvPoint2D32f*)cvAlloc(max_count*sizeof(points[0][0]));
        status = (char*)cvAlloc(max_count);

}

Points2::~Points2() {

    if( !currBuffsSize.width == 0 ) {
        cvReleaseImage(&tempImage);
        cvReleaseImage(&currGreyImage);
        cvReleaseImage(&prevGreyImage);
        cvReleaseImage(&currPyramid);
        cvReleaseImage(&prevPyramid);
    }
}

void Points2::checkSize(CvSize frameSize) {

    if(frameSize.width != currBuffsSize.width || frameSize.height != currBuffsSize.height) {
        if( !currBuffsSize.width == 0 ) {
            cvReleaseImage(&tempImage);
            cvReleaseImage(&currGreyImage);
            cvReleaseImage(&prevGreyImage);
            cvReleaseImage(&currPyramid);
            cvReleaseImage(&prevPyramid);
        }
        tempImage = cvCreateImage(frameSize, IPL_DEPTH_8U, 3);
        currGreyImage = cvCreateImage(frameSize, IPL_DEPTH_8U, 1);
        prevGreyImage = cvCreateImage(frameSize, IPL_DEPTH_8U, 1);
        currPyramid = cvCreateImage(frameSize, IPL_DEPTH_8U, 1);
        prevPyramid = cvCreateImage(frameSize, IPL_DEPTH_8U, 1);
        currBuffsSize = frameSize;
    }
}

void Points2::retreiveFrame(cv::Mat & frame) {

    CvSize frameSize;
    frameSize.width = frame.size().width;
    frameSize.height = frame.size().height;


    checkSize(frameSize);

    IplImage *dupa = new IplImage(frame);

    cvCopy(dupa,tempImage,0);

    cvCvtColor(tempImage, currGreyImage, CV_BGR2GRAY);

    int i, k;
    int flags = 0;

    if( count > 0 )
    {
        cvCalcOpticalFlowPyrLK( prevGreyImage, currGreyImage, prevPyramid, currPyramid,
            points[0], points[1], count, cvSize(frameSize.width, frameSize.height), 3, status, 0,
            cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), flags );
        flags |= CV_LKFLOW_PYR_A_READY;
        for( i = k = 0; i < count; i++ )
        {
            if( add_remove_pt )
            {
                double dx = pt.x - points[1][i].x;
                double dy = pt.y - points[1][i].y;

                if( dx*dx + dy*dy <= 25 )
                {
                    add_remove_pt = 0;
                    continue;
                }
            }

            if( !status[i] )
                continue;

            points[1][k++] = points[1][i];
            cvCircle( &frame, cvPointFrom32f(points[1][i]), 3, CV_RGB(0,255,0), -1, 8,0);
        }
        count = k;
    }

    if( add_remove_pt && count < max_count )
    {

        points[1][count++] = cvPointTo32f(pt);

        cvFindCornerSubPix( currGreyImage, points[1] + count - 1, 1,
            cvSize(frameSize.width, frameSize.height), cvSize(-1,-1),
            cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
        add_remove_pt = 0;

    }

    CV_SWAP( prevGreyImage, currGreyImage, swapImage );
    CV_SWAP( prevPyramid, currPyramid, swapImage );
    CV_SWAP( points[0], points[1], swap_points );
    delete dupa;
}
