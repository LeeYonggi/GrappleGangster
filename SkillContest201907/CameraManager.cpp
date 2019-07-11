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
	Matrix proj, mat;
	D3DXMatrixLookAtLH(&mat, &position, &at, &up);
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI / 3.f, 16.f/ 9.f, 0, 10000.0f);

	DEVICE->SetTransform(D3DTS_VIEW, &mat);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}
