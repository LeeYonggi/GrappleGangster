#include "DXUT.h"
#include "AnimeEffect.h"

AnimeEffect::AnimeEffect(float time, vector<Texture*> anime)
{
	timer = Timer::AddTimer(time);
	textures = anime;
	maxTime = time;
}

AnimeEffect::~AnimeEffect()
{
}

void AnimeEffect::Init()
{
}

void AnimeEffect::Update()
{
	if (timer->IsEnd)
	{
		SetDestroy(true);
		SetActive(false);
	}
}

void AnimeEffect::Render()
{
	int nowTexture = ((maxTime - timer->GetAnyTime()) / maxTime) * textures.size();

	mainTexture = textures[nowTexture];
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void AnimeEffect::Release()
{
	Timer::RemoveTimer(timer);
}
