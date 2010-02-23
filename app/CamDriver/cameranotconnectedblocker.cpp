#include "cameranotconnectedblocker.h"
#include "configdialog.h"

CameraNotConnectedBlocker::CameraNotConnectedBlocker(ConfigDialog *cdialog)
	: cdialog(cdialog)
{}

bool CameraNotConnectedBlocker::canConnect()
{
	return cdialog != NULL && cdialog->vin != NULL;
}

QString CameraNotConnectedBlocker::toString() {
	return QString("Kamera nie podlaczona.");
}
