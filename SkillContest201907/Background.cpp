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

	nowPixelTexture = Resources->LoadTexture("Background/Background_Pixel.png");

	PushBackGround();
	PushBackGround();
	PushBackGround();
}

void Background::Update()
{
	// 메인 배경 움직임
	for (int i = 0; i < texturePosition.size(); i++)
	{
		texturePosition[i] -= Vector3(moveSpeed * ELTime, 0, 0);
	}
	// 메인 배경 조건문
	if (texturePosition[0].x < -SCREEN_X)
	{
		//삭제
		texturePosition.erase(texturePosition.begin());
		mainTextures.erase(mainTextures.begin());
		pixelTextures.erase(pixelTextures.begin());

		if(texturePosition.size() < 4)
			PushBackGround();
	}

	backPosition -= Vector3(moveSpeed * ELTime * 0.1f, 0, 0);

	if (backPosition.x < -SCREEN_X)
		backPosition.x += SCREEN_X;
}

void Background::Render()
{
	RENDERMANAGER->DrawTexture(backTexture, backPosition, scale);
	RENDERMANAGER->DrawTexture(backTexture, backPosition + Vector3(SCREEN_X, 0, 0), scale);
	RENDERMANAGER->DrawTexture(backTexture, backPosition + Vector3(SCREEN_X, 0, 0), scale);

	for(int i = 0; i < mainTextures.size(); i++)
		RENDERMANAGER->DrawTexture(mainTextures[i], texturePosition[i], scale);
}

void Background::Release()
{
}

void Background::PushBackGround()
{
	Vector3 lastPosition = Vector3(0, 0, 720);
	if(texturePosition.size() == 0)
		lastPosition.x = -SCREEN_X;
	else
		lastPosition = *texturePosition.rbegin();

	// 삽입
	texturePosition.push_back(lastPosition + Vector3(SCREEN_X, 0, 0));

	mainTextures.push_back(mainTexture);

	pixelTextures.push_back(nowPixelTexture);
}

// 렉걸리면 바꾸는거 1순위
Background::GROUND_COLLISION Background::IsGroundCollision(Vector2 pos)
{
	GROUND_COLLISION collisionState = GROUND_COLLISION::NONE;

	for (int i = 0; i < pixelTextures.size(); i++)
	{
		D3DLOCKED_RECT lockRect = { 0 };

		pixelTextures[i]->tex->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);

		int width = pixelTextures[i]->info.Width;
		int height = pixelTextures[i]->info.Height;

		int x = width * 0.5f + pos.x - texturePosition[i].x;
		int y = height * 0.5f - pos.y - texturePosition[i].y;

		if (x < 0 || y < 0 ||
			x > width || y > height)
		{
			pixelTextures[i]->tex->UnlockRect(0);
			continue;
		}

		DWORD* pBits = (DWORD*)lockRect.pBits;
		Color color = pBits[width * y + x];

		if (color == Color(1, 0, 1, 1))
		{
			pixelTextures[i]->tex->UnlockRect(0);

			return GROUND_COLLISION::UNACCESS;
		}

		pixelTextures[i]->tex->UnlockRect(0);
	}

	return collisionState;
}
