#include "DXUT.h"
#include "BackEffect.h"

void BackEffect::Init()
{
	pos = Vector3(0, 0, 500);
	mainTexture = Resources->LoadTexture("Effect/BackEffect.png");
}

void BackEffect::Update()
{

}

void BackEffect::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void BackEffect::Release()
{
}
