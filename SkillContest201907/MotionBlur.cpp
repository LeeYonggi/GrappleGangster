#include "DXUT.h"
#include "MotionBlur.h"

#include "MotionEffect.h"

MotionBlur::MotionBlur(GameObject* targetObj)
{
	obj = targetObj;
	pos.z = obj->GetPos().z;
	timer = Timer::AddTimer(0.05f);
}

MotionBlur::~MotionBlur()
{
}

void MotionBlur::Init()
{
}

void MotionBlur::Update()
{
	static bool f = false;

	if (INPUTMANAGER->IsKeyDown(VK_SPACE)) f = !f;

	if (f) 
	{
		Timer::SetTimeScale(Lerp(Timer::GetTimeScale(), 0.1f, 0.05f)); 
	}
	else {
		Timer::SetTimeScale(Lerp(Timer::GetTimeScale(), 1.0f, 0.05f)); 
	}

	if (timer->IsEnd)
	{
		MotionEffect* effect = new MotionEffect(0.15f, obj->GetTexture(), Vector3(-300, 0, 0.1f));
		effect->SetPos(obj->GetPos());

		OBJECTMANAGER->AddGameObject(effect, GameObject::EFFECT);
		timer->Reset(0.01f);
	}
}

void MotionBlur::Render()
{
}

void MotionBlur::Release()
{
	Timer::RemoveTimer(timer);
}
