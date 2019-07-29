#include "DXUT.h"
#include "EndingScene.h"

#include "MainScene.h"

void EndingScene::Init()
{
	texture = Resources->LoadTexture("Ending/ending.png");
}

void EndingScene::Update()
{
	color.a += 0.05f;

	if (INPUTMANAGER->IsKeyDown(VK_LBUTTON))
		SCENEMANAGER->AddScene(new MainScene(), true);
}

void EndingScene::Render()
{
	RENDERMANAGER->DrawSprite(texture, { 640, 360, 0 }, { 1, 1 }, {1, 1}, min(color.a, 1.0f) * 1440, color);
}

void EndingScene::Release()
{
}
