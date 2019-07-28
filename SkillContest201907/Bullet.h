#pragma once
#include "GameObject.h"

class MotionBlur;
class AnimeEffect;
class Bullet
	: public GameObject
{
private:
	Timer* timer;
	Vector3 moveVector;

	MotionBlur* motion;
	AnimeEffect* animeEffect = nullptr;

	bool isInfluenceBackground = true;
	Vector3 target = Vector3(0, 0, 0);

public:
	Bullet(Texture* tex, Vector3 dir) : GameObject(tex), moveVector(dir) {}

	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetInFluenceBackground(bool value) { isInfluenceBackground = value; }
	Vector3 GetMoveVector() { return moveVector; }
	void SetTargetZ(Vector3 value) { target = value; }
};

