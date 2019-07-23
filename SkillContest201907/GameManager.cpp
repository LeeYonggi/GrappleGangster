#include "DXUT.h"
#include "GameManager.h"

#include "Enemy.h"
#include "Enemy1.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	OBJECTMANAGER->AddGameObject(new Enemy1(Vector3(SCREEN_X * 0.5f - 200, -100, 0), Vector3(SCREEN_X * 0.6f, -100, 0)),
		GameObject::ENEMY);
}

void GameManager::Update()
{
}

void GameManager::Render()
{
}

void GameManager::Release()
{
}
