#ifndef CAMERANOTCONNECTEDBLOCKER_H
#define CAMERANOTCONNECTEDBLOCKER_H

#include <bconnectionblocker.h>

class ConfigDialog;

/*! \brief Obiekt blokujący jeżeli nie podpięta kamera */
class CameraNotConnectedBlocker : public BConnectionBlocker {
public:

	/*! \brief To jest konstruktor, jeśli by ktoś nie wiedział

	@param cdialog wskaźnik na config dialog */
	CameraNotConnectedBlocker(ConfigDialog * cdialog);

	/*! \brief Pozwala na połączenie jeśli podłączona jest kamera */
	bool canConnect();

	/*! \brief Zwraca w stringu informację o popełnionym przestępstwie */
	QString toString();
private:
	ConfigDialog * cdialog;
};

#endif // CAMERANOTCONNECTEDBLOCKER_H
