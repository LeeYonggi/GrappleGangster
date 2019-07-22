#pragma once
#include "Singleton.h"

class Enemy;
class GameManager :
	public Singleton<GameManager>
{
public:
	GameManager();
	virtual ~GameManager();

private:
	int enemyCount = 0;

public:
	void Init();
	void Update();
	void Render();
	void Release();

};

#define GAMEMANAGER GameManager::GetInstance()