#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
	position = { 0, 0, -10};
	at = {0, 0, 0};
	up = {0, 1, 0};
}


CameraManager::~CameraManager()
{
}

void CameraManager::SetCamera()
{
	D3DXMatrixLookAtLH(&view, &position, &at, &up);
	D3DXMatrixOrthoLH(&proj, SCREEN_X * cameraSize, SCREEN_Y * cameraSize, 1, 10000.0f);

	DEVICE->SetTransform(D3DTS_VIEW, &view);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}
