#include "DXUT.h"
#include "InGameScene.h"

#include "Player.h"
#include "Background.h"
#include "Enemy1.h"

void InGameScene::Init()
{
	GAMEMANAGER->Reset();
	GAMEMANAGER->Init();
}

void InGameScene::Update()
{
	GAMEMANAGER->Update();
}

void InGameScene::Render()
{
	GAMEMANAGER->Render();
}

void InGameScene::Release()
{
	GAMEMANAGER->Release();
}
