#pragma once
#include "GameObject.h"

class MotionBlur;
class Bullet
	: public GameObject
{
private:
	Timer* timer;
	Vector3 moveVector;

	MotionBlur* motion;

public:
	Bullet(Texture* tex, Vector3 dir) : GameObject(tex), moveVector(dir) {}

	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

