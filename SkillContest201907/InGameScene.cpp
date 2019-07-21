#include "DXUT.h"
#include "InGameScene.h"

#include "Player.h"
#include "Background.h"

void InGameScene::Init()
{
	OBJECTMANAGER->AddGameObject(new Player());
	OBJECTMANAGER->AddGameObject(new Background());
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
