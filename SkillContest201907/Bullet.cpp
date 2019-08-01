#include "DXUT.h"
#include "Bullet.h"

#include "MotionBlur.h"
#include "Cartridge.h"
#include "AnimeEffect.h"
#include "AnimeEffect.h"

void Bullet::Init()
{
	timer = Timer::AddTimer(3.0f);

	motion = new MotionBlur(this, MOTION_MANAGED);
	motion->SetInFluenceBackground(false);

	OBJECTMANAGER->AddGameObject(motion, GameObject::EFFECT);

	radius = 5.0f;

	SOUNDMANAGER->AddSound("bullet", L"./Resources/Music/bullet.wav");
	SOUNDMANAGER->DuplicatePlay("bullet");

	if (!isInfluenceBackground)
	{
		vector<Texture*> anime;
		anime.push_back(Resources->LoadTexture("Effect/Warring_Sign.png"));
		animeEffect = new AnimeEffect(3.0f, anime);
		OBJECTMANAGER->AddGameObject(animeEffect, EFFECT);
	}
}

void Bullet::Update()
{
	pos += moveVector * ELTime;
	rotate = GetVec2ToDegree(Vector2(pos), Vector2(pos) + Vector2(moveVector));

	pos.z = FixZToY(pos.y);

	if(!isInfluenceBackground)
	{
		animeEffect->SetPos(target);
	}
	if(pos.z < target.z && !isInfluenceBackground)
	{
		vector<Texture*> anime = Resources->LoadTextures("Effect/splash/%d.png", 1, 9);
		
		AnimeEffect* effect = new AnimeEffect(0.8f, anime);

		OBJECTMANAGER->AddGameObject(effect, GAMEOBJECT_STATE::EFFECT);

		effect->SetScale(Vector2(2, 2));

		effect->SetPos(pos);

		SetDestroy(true);
	}
	if (timer->IsEnd)
	{
		SetDestroy(true);
	}
}

void Bullet::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Bullet::Release()
{
	Timer::RemoveTimer(timer);
	motion->SetDestroy(true);
	if (animeEffect)
		animeEffect->SetDestroy(true);
}

