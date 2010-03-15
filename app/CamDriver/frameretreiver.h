#ifndef FRAMERETREIVER_H
#define FRAMERETREIVER_H

#include <QImage>

#include <opencv/cv.h>

class VideoInput;

/*! \brief Klasa definiująca interfejs dla klas odbierających ramki obrazu

Użytkownik implementuje jedną z dwóch metod retreiveFrame() */
class FrameRetreiver
{
public:
	/*! \brief Konstruktor

	  @param input powoduje, ze wszystkie ramki z inputu trafią też tu. */
	FrameRetreiver(VideoInput * input);

	/*! \brief Ustawia wejście

	  Dodaje się przez VideoInput::addObserver() do inputu */
	void setInput(VideoInput * input);

	/*! \brief Wypisuje się z obserwowanego wejścia */
	virtual ~FrameRetreiver();

	/*! \brief Odbiera ramkę jako QImage

 do samodzielnej implementacji */
	virtual void retreiveFrame(QImage &);

	/*! \brief Odbiera ramkę jako cv::Mat

	  do samodzielnej implementacji */
	virtual void retreiveFrame(cv::Mat &);
private:
	VideoInput * input;
};

#endif // FRAMERETREIVER_H
