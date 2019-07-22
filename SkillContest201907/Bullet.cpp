#include "DXUT.h"
#include "Bullet.h"

void Bullet::Init()
{
	timer = Timer::AddTimer(3.0f);
}

void Bullet::Update()
{
	pos += moveVector * ELTime;
	rotate = GetVec2ToDegree(Vector2(pos), Vector2(pos) + Vector2(moveVector));

	if (timer->IsEnd)
	{
		Timer::RemoveTimer(timer);
		SetDestroy(true);
	}
}

void Bullet::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Bullet::Release()
{
}
