#include "DXUT.h"
#include "InGameUI.h"

#include "Gun.h"

void InGameUI::Init()
{
	mainTexture = Resources->LoadTexture("UI/InGame/Main.png");
	hpUI = Resources->LoadTexture("UI/InGame/Heart.png");
	box1 = Resources->LoadTexture("UI/InGame/WeaponBox1.png");
	box2 = Resources->LoadTexture("UI/InGame/WeaponBox2.png");
}

void InGameUI::Update()
{
}

void InGameUI::Render()
{
	RENDERMANAGER->DrawSprite(mainTexture, {640, 360, 0});
	RENDERMANAGER->DrawSprite(box1, { 1155, 40, 0 });
	RENDERMANAGER->DrawSprite(box2, { 1230, 40, 0 });

	int i = 0;
	for (auto iter : Player::mainPlayer->gun)
	{
		if (iter == nullptr) continue;
		Texture* gunTexture = iter->GetTexture();
		RENDERMANAGER->DrawSprite(gunTexture, { 1155 + (75.0f * i), 40, 0 });
		i++;
	}
}

void InGameUI::Release()
{
}
