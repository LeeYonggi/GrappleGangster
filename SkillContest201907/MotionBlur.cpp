#include "DXUT.h"
#include "MotionBlur.h"

#include "MotionEffect.h"

MotionBlur::MotionBlur(GameObject* targetObj, TARGET_STATE state)
{
	obj = targetObj;
	pos.z = obj->GetPos().z;
	timer = Timer::AddTimer(0.05f);
	targetState = state;
}

MotionBlur::~MotionBlur()
{
}

void MotionBlur::Init()
{
}

void MotionBlur::Update()
{
	if (timer->IsEnd)
	{
		MotionEffect* effect;
		if(isInfluenceBackground)
			effect = new MotionEffect(0.15f, obj->GetTexture(), Vector3(-300, 0, 0.1f));
		else
			effect = new MotionEffect(0.15f, obj->GetTexture(), Vector3(0, 0, 0.1f));

		effect->state = targetState;

		Vector3 effectPos = obj->GetPos();

		effectPos.z = 400;
		effect->SetPos(effectPos);
		effect->SetRotate(obj->GetRotate());

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
