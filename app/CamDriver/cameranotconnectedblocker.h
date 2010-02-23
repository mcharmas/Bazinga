#ifndef CAMERANOTCONNECTEDBLOCKER_H
#define CAMERANOTCONNECTEDBLOCKER_H

#include <bconnectionblocker.h>

class ConfigDialog;

class CameraNotConnectedBlocker : public BConnectionBlocker {
public:
	CameraNotConnectedBlocker(ConfigDialog * cdialog);
	bool canConnect();

	QString toString();
private:
	ConfigDialog * cdialog;
};

#endif // CAMERANOTCONNECTEDBLOCKER_H
