#pragma once
#include "GameObject.h"

#include "MotionBlur.h"
class MotionBlur;
enum TARGET_STATE;
class MotionEffect :
	public GameObject
{
public:
	MotionEffect(float _time, Texture *_texture, Vector3 _moveVector);
	virtual ~MotionEffect();

public:
	Timer* timer = nullptr;
	TARGET_STATE state = TARGET_STATE::MOTION_MANAGED;

private:
	Vector3 moveVector = Vector3(0, 0, 0);

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

