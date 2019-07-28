#include "DXUT.h"
#include "ChargeUI.h"

ChargeUI::ChargeUI(Texture* _back, Texture* texture, Vector2 _distance, int* chargeCount)
	: GameUI(texture)
{
	distance = _distance;
	charge = chargeCount;
	back = _back;
}

ChargeUI::~ChargeUI()
{
}

void ChargeUI::Init()
{
}

void ChargeUI::Update()
{
}

void ChargeUI::Render()
{
	if(!charge) return;

	if (back)
		RENDERMANAGER->DrawSprite(back, pos + Vector3(distance), scale, {1, 1}, rotate, color);
	for (int i = 0; i < *charge; i++)
		RENDERMANAGER->DrawSprite(mainTexture, pos + Vector3(distance) * i, scale, length, rotate, color);
}

void ChargeUI::Release()
{
}
