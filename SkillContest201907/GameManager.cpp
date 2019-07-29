#include "DXUT.h"
#include "GameManager.h"

#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "InGameUI.h"
#include "BackGround.h"
#include "Car1.h"
#include "Boss.h"
#include "EndingScene.h"
#include "ChargeUI.h"
#include "MainScene.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	background = OBJECTMANAGER->AddGameObject(new Background(), GameObject::BACKGROUND);

	Player *player = OBJECTMANAGER->AddGameObject(new Player(), GameObject::PLAYER);

	OBJECTMANAGER->AddGameObject(new InGameUI(), GameObject::UI);

	int time = GetRandomNumberBetween(10, 20);
	carTimer = Timer::AddTimer(time);

	hpUi = new ChargeUI(nullptr, Resources->LoadTexture("UI/InGame/Heart.png"), { 70, 0 }, &hp);
	hpUi->SetPos({ 195, 30, 0 });

	OBJECTMANAGER->AddGameObject(hpUi, GameObject::UI);
}

void GameManager::Update()
{
	if (hp == 0 && isPlayerDie)
	{
		nowOverImage += 0.2f;

		if (INPUTMANAGER->IsKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->AddScene(new MainScene, true);
			Timer::SetTimeScale(1.0f);
		}
	}
	else if (isPlayerDie)
	{
		wave -= 1;
		Reload();

		return;
	}
	if (endTimer == nullptr && isStageChange)
	{
		wave = 0;
		Reload();
		isStageChange = false;
		SCENEMANAGER->SetSceneChangeEffect(true);
	}
	if (endTimer && endTimer->IsEnd)
	{
		SCENEMANAGER->AddScene(new EndingScene(), true);
	}
	
	if (carTimer && carTimer->IsEnd && stage == STAGE_1)
	{
		int time = GetRandomNumberBetween(10, 20);

		carTimer->Reset(time);

		car = new Car1(background);

		OBJECTMANAGER->AddGameObject(car, GameObject::ENEMY);
	}
	StageUpdate();
}

void GameManager::Render()
{
	if (gameOver.size() == 0) return;
	if (gameOver.size() > nowOverImage)
		nowOverImage = gameOver.size() - 1;
	RENDERMANAGER->DrawSprite(gameOver[(int)nowOverImage], {640, 360, 0});
}

void GameManager::Release()
{
}

void GameManager::Reset()
{
	enemyCount = 0;
	wave = 0;
	maxWave = 10;
	hp = 2;
	background = nullptr;
	carTimer = nullptr;
	isPlayerDie = false;
	isStageChange = false;
	stage = STAGE_1;
	car = nullptr;
	endTimer = nullptr;
	gameOver.clear();
	nowOverImage = 0.0f;

	maxWave = 1;
}

void GameManager::CreateEnemy1()
{
	int maxY = 0;
	switch (stage)
	{
	case STAGE_1:
		maxY = -50;
		break;
	default:
		maxY = -100;
		break;
	}
	int y = GetRandomNumberBetween(-350, maxY);
	float x = GetRandomNumberBetween(200, 400);
	float spawnX = SCREEN_X;
	int spawn = GetRandomNumberBetween(0, 1);

	if (spawn)
		spawnX = -spawnX;
	else
		x = -x;
	OBJECTMANAGER->AddGameObject(new Enemy1(Vector3(spawnX * 0.5f + x, y, 0),
		Vector3(spawnX * 0.8f, y, 0), Player::mainPlayer), GameObject::ENEMY);
}

void GameManager::CreateEnemy2()
{
	int maxY = 0;
	switch (stage)
	{
	case STAGE_1:
		maxY = -50;
		break;
	default:
		maxY = -100;
		break;
	}
	int y = GetRandomNumberBetween(-350, maxY);
	float x = GetRandomNumberBetween(200, 400);

	float spawnX = SCREEN_X;
	int spawn = GetRandomNumberBetween(0, 1);

	if (spawn)
		spawnX = -spawnX;
	else
		x = -x;
	OBJECTMANAGER->AddGameObject(new Enemy2(Vector3(spawnX * 0.5f + x, y, 0),
		Vector3(spawnX * 0.8f, y, 0), Player::mainPlayer), GameObject::ENEMY);
}

void GameManager::CreateBoss()
{
	boss = OBJECTMANAGER->AddGameObject(new Boss(Vector3(SCREEN_X * 0.5f - 300, 0, 0),
		Vector3(SCREEN_X * 0.7f, 0, 0), Player::mainPlayer), GameObject::ENEMY);
}

void GameManager::PlayerDie()
{
	if (hp == 0) return;
	if (hp == 1)
	{
		Timer::SetTimeScale(0.0f);
		gameOver = Resources->LoadTextures("UI/game_over/%d.png", 1, 6);
		Player::mainPlayer->SetCinemaState(Character::PLAYER_END);
	}

	hp -= 1;
	isPlayerDie = true;
}

void GameManager::ChangeStage()
{
	switch (stage)
	{
	case STAGE_1:
		stage = STAGE_2;
		break;
	case STAGE_2:
		stage = STAGE_3;
		break;
	case STAGE_3:
		endTimer = Timer::AddTimer(1.0f);
		break;
	default:
		break;
	}
	isStageChange = true;
}

void GameManager::StageUpdate()
{
	switch (stage)
	{
	case STAGE_3:
		maxWave = 1;
		if (wave < maxWave)
		{
			CreateBoss();
			wave++;
		}
		break;
	default:
		maxWave = 10;
		if (wave < maxWave && enemyCount == 0)
		{
			int count = GetRandomNumberBetween(wave - 2, wave);
			count = min(max(count, 2), 8);
			for (int i = 0; i < count; i++)
			{
				int number = GetRandomNumberBetween(0, 10);
				if (number < 8)
					CreateEnemy1();
				else
					CreateEnemy2();
			}
			if (wave == 7)
				background->PushWaveGround();
			wave++;
		}
		if (wave == maxWave && enemyCount == 0)
		{
			Player::mainPlayer->SetCinemaState(Character::STAGE_END);

			carTimer = nullptr;
			if (car)
				car->SetDestroy(true);
		}
		break;
	}
}

void GameManager::Reload()
{
	enemyCount = 0;

	CAMERAMANAGER->Release();
	OBJECTMANAGER->Release();

	Timer::RemoveAll();
	isPlayerDie = false;

	CAMERAMANAGER->Init();
	OBJECTMANAGER->Init();

	Init();
}
