#include "DXUT.h"
#include "InGameScene.h"

#include "Player.h"
#include "Background.h"

void InGameScene::Init()
{
	OBJECTMANAGER->AddGameObject(new Player(), GameObject::PLAYER);
	OBJECTMANAGER->AddGameObject(new Background(), GameObject::BACKGROUND);
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
