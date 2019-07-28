#include "DXUT.h"
#include "MainProc.h"

#include "MainScene.h"

MainProc::MainProc()
{
}


MainProc::~MainProc()
{
}

void MainProc::Init()
{
	SCENEMANAGER->AddScene(new MainScene(), false);
}

void MainProc::Update()
{
	CAMERAMANAGER->Update();

	OBJECTMANAGER->Update();

	SCENEMANAGER->Update();

	INPUTMANAGER->KeyUpdate();
}

void MainProc::Render()
{
	CAMERAMANAGER->SetCamera();

	OBJECTMANAGER->Render();
	
	SCENEMANAGER->Render();

	INPUTMANAGER->Render();
}

void MainProc::Release()
{
	CAMERAMANAGER->ReleaseInstance();
	RENDERMANAGER->ReleaseInstance();
	OBJECTMANAGER->ReleaseInstance();
	SCENEMANAGER->ReleaseInstance();
	INPUTMANAGER->ReleaseInstance();
	GAMEMANAGER->ReleaseInstance();
	Resources->ReleaseInstance();

	Timer::RemoveAll();
}
