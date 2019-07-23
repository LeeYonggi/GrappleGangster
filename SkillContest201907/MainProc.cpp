#include "DXUT.h"
#include "MainProc.h"


MainProc::MainProc()
{
}


MainProc::~MainProc()
{
}

void MainProc::Init()
{
	SCENEMANAGER->AddScene(new InGameScene());
}

void MainProc::Update()
{
	OBJECTMANAGER->Update();

	SCENEMANAGER->Update();

	INPUTMANAGER->KeyUpdate();
}

void MainProc::Render()
{
	CAMERAMANAGER->SetCamera();

	OBJECTMANAGER->Render();
	
	SCENEMANAGER->Render();
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
}
