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

public:
	void SetCamera();
};

#define CAMERAMANAGER CameraManager::GetInstance()