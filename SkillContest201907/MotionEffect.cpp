#include "DXUT.h"
#include "MotionEffect.h"

#include "MotionBlur.h"
MotionEffect::MotionEffect(float _time, Texture* _texture, Vector3 _moveVector)
{
	mainTexture = _texture;
	moveVector = _moveVector;

	timer = Timer::AddTimer(_time);
	color.a = 0.15f;
}

MotionEffect::~MotionEffect()
{
}

void MotionEffect::Init()
{
}

void MotionEffect::Update()
{
	pos += moveVector * ELTime;
	color.a -= 0.5f * ELTime;

	if (timer->IsEnd)
	{
		SetDestroy(true);
	}
}

void MotionEffect::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void MotionEffect::Release()
{
	Timer::RemoveTimer(timer);
}
