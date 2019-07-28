#include "DXUT.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	sceneChange = Resources->LoadTextures("UI/next_go_scence/%d.png", 1, 17);
}

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::AddScene(Scene* scene, bool isSceneChangeEffect)
{
	nextScene = scene;
	isSceneChange = isSceneChangeEffect;
}

void SceneManager::Update()
{
	if ((!isSceneChange && nextScene) || (nextScene && nowSceneChangeTexture >= 8))
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

	if (isSceneChange)
	{
		RENDERMANAGER->DrawSprite(sceneChange[(int)nowSceneChangeTexture],
			Vector3(SCREEN_X * 0.5f, SCREEN_Y * 0.5f, 0));

		nowSceneChangeTexture += 0.2f;

		if (nowSceneChangeTexture >= sceneChange.size())
		{
			nowSceneChangeTexture = 0;
			isSceneChange = false;
		}
	}
}

void SceneManager::Release()
{
	SAFE_RELEASE(nowScene);
	SAFE_RELEASE(nextScene);
	
	SAFE_DELETE(nowScene);
	SAFE_DELETE(nextScene);
}
