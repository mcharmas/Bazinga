#ifndef FACES_H
#define FACES_H

#include <QObject>
#include <vector>
#include <boblist.h>
#include "frameretreiver.h"

/*! \brief Wykrywa twarze */
class Faces : public QObject, public FrameRetreiver
{
	Q_OBJECT
public:
	//! Pobieraj z danego wejścia
	Faces(VideoInput* input);
	void retreiveFrame(cv::Mat &);

signals:
	//! emituje obiekty typu BOb
	void bobjects(BObList * list);

private:
	cv::CascadeClassifier haar;

	BObList bobs;

	std::vector<cv::Rect> objects;

};

#endif // FACES_H
