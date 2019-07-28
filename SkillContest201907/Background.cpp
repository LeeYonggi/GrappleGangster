#include "DXUT.h"
#include "Background.h"

Background::Background()
{
	pos.z = 720;
	backPosition.z = 800;
	backPosition2.z = 800;
}

Background::~Background()
{
}

void Background::Init()
{
	switch (GAMEMANAGER->stage)
	{
	case STAGE_1:
		mainTexture = Resources->LoadTexture("Background/Background.png");

		backTexture = Resources->LoadTexture("Background/Background3.png");

		nowPixelTexture = Resources->LoadTexture("Background/Background_Pixel.png");

		moveSpeed = 1200.0f;
		break;
	case STAGE_2:
		mainTexture = Resources->LoadTexture("Background2/Background1.png");

		backTexture = Resources->LoadTexture("Background2/Background3.png");

		backTexture2 = Resources->LoadTexture("Background2/Background2.png");

		nowPixelTexture = Resources->LoadTexture("Background2/Background_Pixel.png");
		moveSpeed = 1000.0f;
		break;
	case STAGE_3:
		mainTexture = Resources->LoadTexture("Background3/Background1.png");

		backTexture = Resources->LoadTexture("Background3/Background2.png");

		nowPixelTexture = Resources->LoadTexture("Background3/Background_Pixel.png");

		moveSpeed = 300.0f;
		break;
	default:
		break;
	}

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
		// 배경 리스트 반복
		CyclingGround();
	}

	backPosition -= Vector3(moveSpeed * ELTime * 0.1f, 0, 0);

	if (backPosition.x < -SCREEN_X)
		backPosition.x += SCREEN_X;

	if (backTexture2)
	{
		backPosition2 -= Vector3(moveSpeed * ELTime * 0.5f, 0, 0);

		if (backPosition2.x < -SCREEN_X)
			backPosition2.x += SCREEN_X;
	}
}

void Background::Render()
{
	RENDERMANAGER->DrawTexture(backTexture, backPosition, scale);
	RENDERMANAGER->DrawTexture(backTexture, backPosition + Vector3(SCREEN_X, 0, 0), scale);
	RENDERMANAGER->DrawTexture(backTexture, backPosition + Vector3(SCREEN_X, 0, 0), scale);

	if (backTexture2)
	{
		RENDERMANAGER->DrawTexture(backTexture2, backPosition2, scale);
		RENDERMANAGER->DrawTexture(backTexture2, backPosition2 + Vector3(SCREEN_X, 0, 0), scale);
		RENDERMANAGER->DrawTexture(backTexture2, backPosition2 + Vector3(SCREEN_X, 0, 0), scale);
	}

	for(int i = 0; i < mainTextures.size(); i++)
		RENDERMANAGER->DrawTexture(mainTextures[i], texturePosition[i], scale);
}

void Background::Release()
{
	mainTextures.clear();
	pixelTextures.clear();
	pixelColor.clear();
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

	D3DLOCKED_RECT lockRect = { 0 };

	(*pixelTextures.rbegin())->tex->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD* pBits = (DWORD*)lockRect.pBits;
	(*pixelTextures.rbegin())->tex->UnlockRect(0);

	pixelColor.push_back(pBits);
}

void Background::PushWaveGround()
{
	if (GAMEMANAGER->stage != STAGE_1) return;

	mainTexture = Resources->LoadTexture("Background/WaveGround.png");

	nowPixelTexture = Resources->LoadTexture("Background/WaveGround_Pixel.png");

	PushBackGround();
}

void Background::CyclingGround()
{
	//삭제
	texturePosition.erase(texturePosition.begin());

	Texture* texture = *mainTextures.begin();
	Texture* pixelTexture = *pixelTextures.begin();
	mainTextures.erase(mainTextures.begin());
	pixelTextures.erase(pixelTextures.begin());
	pixelColor.erase(pixelColor.begin());

	if (texturePosition.size() > 3) return;

	texturePosition.push_back(*texturePosition.rbegin() + Vector3(SCREEN_X, 0, 0));

	mainTextures.push_back(texture);

	pixelTextures.push_back(pixelTexture);

	D3DLOCKED_RECT lockRect = { 0 };

	(*pixelTextures.rbegin())->tex->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD* pBits = (DWORD*)lockRect.pBits;
	(*pixelTextures.rbegin())->tex->UnlockRect(0);

	pixelColor.push_back(pBits);
}


Background::GROUND_COLLISION Background::IsGroundCollision(Vector2 pos)
{
	GROUND_COLLISION collisionState = GROUND_COLLISION::NONE;

	for (int i = 0; i < pixelTextures.size(); i++)
	{
		int width = pixelTextures[i]->info.Width;
		int height = pixelTextures[i]->info.Height;

		int x = width * 0.5f + pos.x - texturePosition[i].x;
		int y = height * 0.5f - pos.y - texturePosition[i].y;

		if (x < 0 || y < 0 ||
			x > width || y > height)
		{
			continue;
		}

		Color color = pixelColor[i][width * y + x];

		if (color == Color(1, 0, 1, 1))
		{
			return GROUND_COLLISION::UNACCESS_DOWN;
		}
		if (color == Color(0, 0, 1, 1))
		{
			return GROUND_COLLISION::UNACCESS_UP;
		}

	}

	return collisionState;
}
