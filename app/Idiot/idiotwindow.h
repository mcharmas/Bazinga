#ifndef IDIOTWINDOW_H
#define IDIOTWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTimerEvent>
#include <bconnection.h>

namespace Ui {
    class IdiotWindow;
}

/*! \brief Klasa wyświetlająca okno programu

  Składa się tylko z dwóch pól:
  \li po lewej kolorowa reprezentacja otrzymanych obiektow ImageWidget
  \li po prawej panel do nawiązania połączenia BConnectionWidget
*/
class IdiotWindow : public QMainWindow {
    Q_OBJECT
public:

	/*! \brief Konstruktor

	  Włącza timer co 10 ms.
	  \sa timerEvent(QTimerEvent*)
	  */
    IdiotWindow(QWidget *parent = 0);

	/*! \brief Destruktor

	  Rozłącza z serwerem.
	*/
    ~IdiotWindow();

protected:
	/*! \brief Związane z Qt, nie dotyczy programu */
    void changeEvent(QEvent *e);

	/*! \brief Sprawdza, czy przyszły dane

	Jeśli przyszły nowe dane, tworzy z datagramu liste obiektow
	i przekazuje je do ImageWidget::setBObs(quint32, BObList*) */
	void timerEvent(QTimerEvent *ev);

private:
    Ui::IdiotWindow *ui;
	BConnection connection;
	QSettings settings;
};

#endif // IDIOTWINDOW_H
