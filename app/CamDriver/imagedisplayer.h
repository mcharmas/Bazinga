#ifndef IMAGEDISPLAYER_H
#define IMAGEDISPLAYER_H

#include <QWidget>
#include <QImage>
#include <QPaintEvent>
#include <QGroupBox>
#include <QMouseEvent>

/*! \brief Klasa wyświetlają obraz z kamery */
class ImageDisplayer : public QWidget
{
	Q_OBJECT
public:
	//! \brief konstruktor w pełnej krasie i bez argumentów
    ImageDisplayer();
	//! \brief Bardziej złożony konstruktor, ustawia parenta
	ImageDisplayer(QGroupBox*&);

	/*! \brief Ustaw obrazek

	Zazwyczaj potrzeba ustawić tylko raz, bo kamera zapisuje zawsze do tego
	samego obiektu */
	void setImage(QImage * image);

protected:
	//! \brief Maluje obrazek
	void paintEvent(QPaintEvent *);

	//! \brief Wskaźnik do obrazka malowanego na widgetcie
	QImage * image;

private:
	void commonSetup();
	void mouseReleaseEvent(QMouseEvent *e);
};

#endif // IMAGEDISPLAYER_H
