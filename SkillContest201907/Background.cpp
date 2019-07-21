#include "DXUT.h"
#include "Background.h"

Background::Background()
{
	moveSpeed = 1000.0f;
}

Background::~Background()
{
}

void Background::Init()
{
	mainTexture = Resources->LoadTexture("Background/Background.png");
}

void Background::Update()
{
	pos -= Vector3(moveSpeed * ELTime, 0, 0);

	if (pos.x < -1280)
		pos.x += 1280;
}

void Background::Render()
{
	pos.z = 10;
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale);
	RENDERMANAGER->DrawTexture(mainTexture, pos + Vector3(1280, 0, 0), scale);
	RENDERMANAGER->DrawTexture(mainTexture, pos + Vector3(1280, 0, 0), scale);
}

void Background::Release()
{
}
