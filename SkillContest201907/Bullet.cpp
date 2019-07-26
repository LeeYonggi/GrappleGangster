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
		pos.z = FixZToY(pos.y);
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

