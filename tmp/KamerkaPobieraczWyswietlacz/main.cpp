#include "opencv/cv.h"
#include "opencv/highgui.h"

#include <iostream>
//using namespace cv;

int main(int argc, char *argv[])
{
	CvCapture * capture = cvCaptureFromCAM( CV_CAP_ANY );
	if (!capture) {
		std::cerr << "Nie znalazlem kamery\n" ;
		return -1;
	}

	cvNamedWindow("Kamerara", CV_WINDOW_AUTOSIZE);


	while (1) {
		IplImage * frame = cvQueryFrame(capture);
		if (!frame) {
			std::cerr << "Nie moge stworzyc okna";
			break;
		}
		cvShowImage("Kamerara", frame);

		if(cvWaitKey(10) == 27) break;
	}

	cvReleaseCapture( &capture);
	cvDestroyAllWindows();
	return 0;
}
