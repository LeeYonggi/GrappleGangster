#include "DXUT.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::AddScene(Scene* scene)
{
	nextScene = scene;
}

void SceneManager::Update()
{
	if (nextScene)
	{
		SAFE_RELEASE(nowScene);
		SAFE_DELETE(nowScene);

		OBJECTMANAGER->Release();
		OBJECTMANAGER->Init();

		nowScene = nextScene;

		nextScene = nullptr;

		nowScene->Init();
	}
	nowScene->Update();
}

void SceneManager::Render()
{
	nowScene->Render();
}

void SceneManager::Release()
{
	SAFE_RELEASE(nowScene);
	SAFE_RELEASE(nextScene);
	
	SAFE_DELETE(nowScene);
	SAFE_DELETE(nextScene);
}
