#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <vector>

#include <iostream>
#include <vector>
using namespace cv;

#include "fast/cvfast.h"

int main(int argc, char *argv[])
{
	VideoCapture vid(0);

	namedWindow("video", 1);

	Mat frame, mono;
	for(;;) {
		vid >> frame;
		Mat dst = Mat::zeros(frame.rows, frame.cols, CV_8UC3);
		//cvtColor(frame, mono, CV_BGR2GRAY);
		mono = frame > 1;
//		GaussianBlur(mono, mono, Size(9,9), 0, 0);
//		Canny(mono, mono, 0, 30, 3);
//
//		std::vector<Mat> colors;
//		split(frame, colors);
//		for(int i = 0; i < colors.size(); ++i) {
//			add(colors[i], mono, colors[i]);
//		}
//		merge(colors, frame);

		//GaussianBlur(frame, frame, Size(7,7), 0, 0);
		vector< vector<Point> > contours;
		vector<Vec4i> hier;
		findContours(mono, contours, hier, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		for( int idx = 0; idx >= 0; idx = hier[idx][0]) {
			 Scalar color( rand()&255, rand()&255, rand()&255 );
			 drawContours(dst, contours, idx, color, CV_FILLED, 8, hier);
		}

		imshow("video", dst);

//		Mat sha
//		filter2D(
		if(waitKey(70) >= 0) break;
	}

	return 0;
}
