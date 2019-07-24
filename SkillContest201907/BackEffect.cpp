#include "DXUT.h"
#include "BackEffect.h"

void BackEffect::Init()
{
	pos = Vector3(0, 0, 500);
	mainTexture = Resources->LoadTexture("Effect/BackEffect.png");
	subTexture = Resources->LoadTexture("Effect/light.png");
}

void BackEffect::Update()
{
}

void BackEffect::Render()
{
	RENDERMANAGER->DrawCircleTexture(mainTexture, 0.1f, pos, scale, rotate, color);
}

void BackEffect::Release()
{
}
