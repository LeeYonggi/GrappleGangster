#include "DXUT.h"
#include "Background.h"

Background::Background()
{
	moveSpeed = 1200.0f;
	pos.z = 720;
	backPosition.z = 800;
}

Background::~Background()
{
}

void Background::Init()
{
	mainTexture = Resources->LoadTexture("Background/Background.png");
	backTexture = Resources->LoadTexture("Background/Background3.png");
}

void Background::Update()
{
	pos -= Vector3(moveSpeed * ELTime, 0, 0);
	backPosition -= Vector3(moveSpeed * ELTime * 0.1f, 0, 0);

	if (pos.x < -SCREEN_X)
		pos.x += SCREEN_X;
	if (backPosition.x < -SCREEN_X)
		backPosition.x += SCREEN_X;
}

void Background::Render()
{
	RENDERMANAGER->DrawTexture(backTexture, backPosition, scale);
	RENDERMANAGER->DrawTexture(backTexture, backPosition + Vector3(SCREEN_X, 0, 0), scale);
	RENDERMANAGER->DrawTexture(backTexture, backPosition + Vector3(SCREEN_X, 0, 0), scale);

	RENDERMANAGER->DrawTexture(mainTexture, pos, scale);
	RENDERMANAGER->DrawTexture(mainTexture, pos + Vector3(SCREEN_X, 0, 0), scale);
	RENDERMANAGER->DrawTexture(mainTexture, pos + Vector3(SCREEN_X, 0, 0), scale);
}

void Background::Release()
{
}
