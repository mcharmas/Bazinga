#include "faces.h"
using namespace std;

Faces::Faces(VideoInput * input) : FrameRetreiver(input), haar("haarcascade_frontalface_default.xml"), objects(0)
{}

void Faces::retreiveFrame(cv::Mat & frame) {
	haar.detectMultiScale(frame, objects, 1.4, 3, 0, cv::Size(40,40));

	double horizProp = (double) 640 / frame.cols;
	double vertProp = (double) 480 / frame.rows;

	bobs.clear();
	for(vector<cv::Rect>::iterator it = objects.begin();
	it != objects.end();
	++it) {
		cv::Rect &r = *it;
		cv::Point p1, p2;
		p1.x = r.x;
		p1.y = r.y;
		p2.x = r.x + r.width;
		p2.y = r.y + r.height;

		bobs.append(BOb((quint16) (horizProp * r.x),
						(quint16) (vertProp * r.y),
						(quint16) (horizProp * r.width),
						(quint16) (vertProp * r.height)));

		cv::rectangle(frame, p1, p2, CV_RGB(255,0,0), 3);
	}
	if(!bobs.empty())
		emit bobjects(&bobs);
}
