#include "DXUT.h"
#include "Bullet.h"

#include "MotionBlur.h"
#include "Cartridge.h"

void Bullet::Init()
{
	timer = Timer::AddTimer(3.0f);

	motion = new MotionBlur(this, MOTION_MANAGED);
	motion->SetInFluenceBackground(false);

	OBJECTMANAGER->AddGameObject(motion, GameObject::EFFECT);

	radius = 5.0f;
}

void Bullet::Update()
{
	pos += moveVector * ELTime;
	rotate = GetVec2ToDegree(Vector2(pos), Vector2(pos) + Vector2(moveVector));

	if (isInfluenceBackground)
		pos.z = pos.y + SCREEN_Y * 0.5f;
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
}

Bullet* Bullet::MakeRifleBullet(Vector3 pos, Vector3 dir, GAMEOBJECT_STATE state, bool isInfluenceBackground)
{
	Bullet* bullet = new Bullet(Resources->LoadTexture("Bullet/Player_Bullet.png"),
		dir * 1000);

	bullet->SetPos(pos);

	bullet->SetInFluenceBackground(isInfluenceBackground);

	OBJECTMANAGER->AddGameObject(bullet, GameObject::PLAYER_BULLET);

	Background* background = (Background*)(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());

	Cartridge* cartridge = new Cartridge(pos, background);

	OBJECTMANAGER->AddGameObject(cartridge, GameObject::EFFECT);

	return nullptr;
}
