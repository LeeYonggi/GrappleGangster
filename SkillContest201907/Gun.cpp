#include "DXUT.h"
#include "Gun.h"

void Gun::Init()
{

}

void Gun::Update()
{

}

void Gun::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Gun::Release()
{
}
