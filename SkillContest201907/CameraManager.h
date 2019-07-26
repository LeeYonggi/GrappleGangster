#pragma once
#include "Singleton.h"
class CameraManager :
	public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

private:
	Vector3 position;
	Vector3 up;
	Vector3 at;

	Matrix proj;
	Matrix view;

	float cameraSize = 1.0f;

	Timer* timeStop;

public:
	Matrix GetProjection() { return proj; }
	Matrix GetView() { return view; }

public:
	void Update();
	void SetCamera();
	void OneStopCamera(float time);
};

#define CAMERAMANAGER CameraManager::GetInstance()