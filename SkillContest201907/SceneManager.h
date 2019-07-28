#pragma once
#include "Singleton.h"
#include "Scene.h"


class SceneManager :
	public Singleton<SceneManager>
{
public:
	SceneManager();
	virtual ~SceneManager();

private:
	Scene* nowScene = nullptr;
	Scene* nextScene = nullptr;
	vector<Texture*> sceneChange;
	float nowSceneChangeTexture = 0;
	bool isSceneChange = false;

public:
	void AddScene(Scene	*scene, bool isSceneChangeEffect);
	void SetSceneChangeEffect(bool isSceneChangeEffect) 
	{
		isSceneChange = isSceneChangeEffect;
	}
	void Update();
	void Render();
	void Release();
};

#define SCENEMANAGER SceneManager::GetInstance()