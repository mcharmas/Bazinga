#ifndef VIDEOINPUT_H
#define VIDEOINPUT_H

#include <QThread>
#include <QMutex>
#include <QList>
#include <QImage>

#include <opencv/cv.h>
#include <opencv/highgui.h>

class FrameRetreiver;

/*! \brief Klasa przechwytująca obraz z kamerki */
class VideoInput : public QThread
{
	Q_OBJECT
public:
	/*! \brief Konstruktor

	  @param frameRate ustaw początkowy framerate */
	VideoInput(int frameRate);
	virtual ~VideoInput();

	/*! \brief Dodaj obserwatora

	  Dodaje na początek listy.
	  Na każdym obserwatorze zostaną wywołane metody obie FrameRetreiver::retreiveFrame() */
	void addObserver(FrameRetreiver *);

	/*! \brief Wywal obserwatora */
	void delObserver(FrameRetreiver *);

	/*! \brief ustaw frame rate */
	void setFrameRate(float frameRate);

	/*! \brief pobierz frame rate */
	float getFrameRate();

public slots:
	/*! \brief bezpiecznie wyłącz pobieranie obrazu i poczekaj */
	void safelyStop();

protected:
	/*! \brief zreimlementowane z QThread

	  Zawiera pętlę, w której pobierany jest obraz.
	*/
	virtual void run();

private:
	void getFrame();

	unsigned long getSleepUTime();

	cv::VideoCapture vid;
	cv::Mat frame;
	QImage image;

	QList<FrameRetreiver*> observers;
	QMutex observersMutex, frameRateMutex;
	float frameRate;
	unsigned long sleepUTime;
	bool running;
};

#endif // VIDEOINPUT_H
