#include "DXUT.h"
#include "InGameScene.h"

#include "Player.h"
#include "Background.h"
#include "Enemy1.h"

void InGameScene::Init()
{
	OBJECTMANAGER->AddGameObject(new Player(), GameObject::PLAYER);
	OBJECTMANAGER->AddGameObject(new Background(), GameObject::BACKGROUND);
	OBJECTMANAGER->AddGameObject(new Enemy1(), GameObject::ENEMY);
}

void InGameScene::Update()
{
}

void InGameScene::Render()
{
}

void InGameScene::Release()
{
}
