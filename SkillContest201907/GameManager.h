#pragma once
#include "Singleton.h"


enum STAGE_STATE
{
	STAGE_1,
	STAGE_2,
	STAGE_3
};
class Background;
class Enemy;
class Car1;
class Boss;
class ChargeUI;
class GameManager :
	public Singleton<GameManager>
{
public:
	GameManager();
	virtual ~GameManager();


public:
	int enemyCount = 0;
	int wave = 0;
	int maxWave = 10;
	int hp = 2;
	Background* background = nullptr;
	Timer* carTimer = nullptr;
	bool isPlayerDie = false;
	bool isStageChange = false;
	STAGE_STATE stage = STAGE_1;
	Car1* car = nullptr;
	Timer* endTimer = nullptr;
	vector<Texture*> gameOver;
	float nowOverImage = 0.0f;

private:
	Boss* boss = nullptr;
	ChargeUI* hpUi = nullptr;

public:
	void Init();
	void Update();
	void Render();
	void Release();
	
	void Reset();

public:
	void CreateEnemy1();
	void CreateEnemy2();
	void CreateBoss();

	void PlayerDie();
	void ChangeStage();

	void StageUpdate();

private:
	void Reload();
};

#define GAMEMANAGER GameManager::GetInstance()