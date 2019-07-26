#include "DXUT.h"
#include "GameManager.h"

#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "InGameUI.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	Player *player = OBJECTMANAGER->AddGameObject(new Player(), GameObject::PLAYER);

	OBJECTMANAGER->AddGameObject(new InGameUI(), GameObject::UI);
	
}

void GameManager::Update()
{
	if (wave < 8 && enemyCount == 0)
	{
		int count = GetRandomNumberBetween(wave - 2, wave);
		count = min(max(count, 2), 8);
		for (int i = 0; i < count; i++)
		{
			int number = GetRandomNumberBetween(0, 10);
			if(number < 8)
				CreateEnemy1();
			else
				CreateEnemy2();
		}
		wave++;
	}
}

void GameManager::Render()
{
}

void GameManager::Release()
{
}

void GameManager::CreateEnemy1()
{
	int y = GetRandomNumberBetween(-350, -50);
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
	int y = GetRandomNumberBetween(-350, -50);
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
