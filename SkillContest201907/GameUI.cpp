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
}

void GameUI::Render()
{
	if (timer)
	{
		int nowTexture = (timer->GetAnyTime() / maxTime) * (animeTexture.size() - 1);
		
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
}
