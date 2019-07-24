#include "DXUT.h"
#include "MotionEffect.h"

#include "MotionBlur.h"

MotionEffect::MotionEffect(float _time, Texture* _texture, Vector3 _moveVector)
{
	mainTexture = _texture;
	moveVector = _moveVector;

	timer = Timer::AddTimer(_time);
}

MotionEffect::~MotionEffect()
{
}

void MotionEffect::Init()
{
	switch (state)
	{
	case MOTION_MANAGED:
		color.a = 0.15f;
		break;
	case MOTION_PLAYER:
		color.a = 0.2f;
		break;
	default:
		break;
	}
}

void MotionEffect::Update()
{
	switch (state)
	{
	case MOTION_MANAGED:
		pos += moveVector * ELTime;
		color.a -= 0.6f * ELTime;
		break;
	case MOTION_PLAYER:
		pos += moveVector * ELTime * ((1.0f - Timer::GetTimeScale()) * 5);
		color.a -= 1.0f * ELTime * Timer::GetTimeScale();
		color.r -= (1.0f - Timer::GetTimeScale()) * 0.01f;
		color.g -= (1.0f - Timer::GetTimeScale()) * 0.1f;
		break;
	default:
		break;
	}

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
