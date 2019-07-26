#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
	position = { 0, 0, -10};
	at = {0, 0, 0};
	up = {0, 1, 0};

	timeStop = Timer::AddTimer(0.0f);
	timeStop->SetIsInfluenceOfTimeScale(false);
}


CameraManager::~CameraManager()
{
}


void CameraManager::Update()
{
	if(timeStop->GetAnyTime() < 0.3)
		Timer::SetTimeScaleMin(1.0f);

	if (timeStop->IsEnd == true)
		position = { 0, 0, -10 };
	else 
	{
		position.x += GetRandomNumberBetween(-6, 6);
		position.y += GetRandomNumberBetween(-6, 6);

		if (position.x > 10 || position.x < -10)
			position.x = 0;
		if (position.y > 10 || position.y < -10)
			position.y = 0;
	}
}

void CameraManager::SetCamera()
{
	at = {position.x, position.y, 0};
	D3DXMatrixLookAtLH(&view, &position, &at, &up);
	D3DXMatrixOrthoLH(&proj, SCREEN_X * cameraSize, SCREEN_Y * cameraSize, 1, 10000.0f);

	DEVICE->SetTransform(D3DTS_VIEW, &view);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}

void CameraManager::OneStopCamera(float time)
{
	Timer::SetTimeScaleMin(0.3f);
	
	position.x += GetRandomNumberBetween(-3, 3);
	position.y += GetRandomNumberBetween(-3, 3);

	timeStop->Reset(time);
}
