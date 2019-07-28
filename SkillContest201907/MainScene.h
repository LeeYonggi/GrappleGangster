#pragma once
#include "Scene.h"

class GameUI;
class MainScene :
	public Scene
{
public:
	GameUI* title = nullptr;
	GameUI* player = nullptr;
	GameUI* enemy = nullptr;
	GameUI* fog1 = nullptr;
	GameUI* fog2 = nullptr;
	Timer* timer = nullptr;
	GameUI* start = nullptr;
	GameUI* howTo = nullptr;
	GameUI* rank = nullptr;
	GameUI* quit = nullptr;
	GameUI* mainHowTo = nullptr;
	GameUI* mainRank = nullptr;
	float playerCos = 0.0f;
	float enemyCos = 0.0f;

public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
};

