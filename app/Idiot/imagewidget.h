#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPen>
#include <QMap>
#include <QStringList>
#include <boblist.h>

/*! \brief Wyświetla obiekty od klientów w różnych kolorach
  */
class ImageWidget : public QWidget
{
Q_OBJECT
public:
	/*! \brief Konstruktor */
    explicit ImageWidget(QWidget *parent = 0);

	/*! \brief Destruktor */
	~ImageWidget();

	/*! \brief Ustawia listę obiektów dla danego id sesji.

	  Wewnętrznie trzymane jest to uzywając QMap z id sesji jako kluczem.
	  Jeśli stara lista dla danego id isntniała to zostaje skasowana.
	  przekazanie list == 0 owocuje całkowitym skasowaniem danego sessid
	  z mapy.
	  */
	void setBObs(quint32 sessid, BObList * list);

protected:
	/*! \brief Maluje obiekty na widgecie

	Przyporządkowuje każdemu sessid przekazanego w setBObs()
	kolor. To samo id sesji zawsze dostanie ten sam kolor.
	Kolory wybierane są spośród ok. 20 zdefiniowanych domyślnie w Qt.
	*/
	void paintEvent(QPaintEvent *ev);

        /*! \brief Klikniecie powoduje wyczyszczenie ekranu */
        void mouseReleaseEvent(QMouseEvent *);

private:
	QMap<quint32, BObList*> boblists;
	QPen pen;
	QStringList colorNames;
};

#endif // IMAGEWIDGET_H
