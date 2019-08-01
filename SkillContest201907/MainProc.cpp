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
	CameraManager::ReleaseInstance();
	RenderManager::ReleaseInstance();
	ObjectManager::ReleaseInstance();
	SceneManager::ReleaseInstance();
	InputManager::ReleaseInstance();
	GameManager::ReleaseInstance();
	ResourceManager::ReleaseInstance();
	SoundManager::ReleaseInstance();

	Timer::RemoveAll();
}
