#pragma once
#include "GameObject.h"

class Background;
class MotionBlur;
class BackEffect;
class Ride;
class Player :
	public GameObject
{
private:
	Vector3 moveVector = Vector3(0, 0, 0);
	MotionBlur* motionBlur = nullptr;
	Timer* timer = nullptr;
	Background *background;
	BackEffect* backEffect;
	Ride* ride = nullptr;

	float moveSpeed = 0.0f;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void PlayerMove();
	void PlayerAttack();
};

