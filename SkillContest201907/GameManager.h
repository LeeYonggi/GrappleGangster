#pragma once
#include "Singleton.h"

class Enemy;
class GameManager :
	public Singleton<GameManager>
{
public:
	GameManager();
	virtual ~GameManager();

public:
	int enemyCount = 0;
	int wave = 0;

public:
	void Init();
	void Update();
	void Render();
	void Release();

public:
	void CreateEnemy1();
	void CreateEnemy2();
};

#define GAMEMANAGER GameManager::GetInstance()