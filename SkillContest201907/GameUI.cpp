#include "DXUT.h"
#include "GameUI.h"

GameUI::GameUI(float time, vector<Texture*> textures)
{
	animeTexture = textures;
	timer = Timer::AddTimer(time);
	maxTime = time;
}

void GameUI::Init()
{
}

void GameUI::Update()
{
	if (!mainTexture) return;
	RECT re = { 0 };
	RECT collision =
	{
		(int)(pos.x - mainTexture->info.Width * 0.5f),
		(int)(pos.y - mainTexture->info.Height * 0.5f),
		(int)(pos.x + mainTexture->info.Width * 0.5f),
		(int)(pos.y + mainTexture->info.Height * 0.5f)
	};
	RECT mouse =
	{
		(int)INPUTMANAGER->GetMousePos().x - 1,
		(int)INPUTMANAGER->GetMousePos().y - 1,
		(int)INPUTMANAGER->GetMousePos().x,
		(int)INPUTMANAGER->GetMousePos().y
	};
	if (IntersectRect(&re, &collision, &mouse))
	{
		tuchEventHandler(this, 0);
		if (downEventHandler.GetSize() > 0)
			color = Color(1, 1, 1, 0.3);
		if (INPUTMANAGER->IsKeyDown(VK_LBUTTON))
		{
			downEventHandler(this, 0);
		}
	}
	else if(downEventHandler.GetSize() > 0)
		color = Color(1, 1, 1, 1);
}

void GameUI::Render()
{
	if (timer)
	{
		int nowTexture = (timer->GetAnyTime() / maxTime) * (animeTexture.size() - 1);
		
		nowTexture = min(nowTexture, maxTime);
		RENDERMANAGER->DrawSprite(animeTexture[nowTexture], pos, scale, length, rotate, color);

		if (timer->IsEnd)
			timer->Reset(maxTime);
	}
	else
		RENDERMANAGER->DrawSprite(mainTexture, pos, scale, length, rotate, color);
}

void GameUI::Release()
{
	if (timer)
		Timer::RemoveTimer(timer);
	downEventHandler.RemoveAll();
}
