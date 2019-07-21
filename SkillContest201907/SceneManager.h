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

public:
	void AddScene(Scene	*scene);
	void Update();
	void Render();
	void Release();
};

#define SCENEMANAGER SceneManager::GetInstance()