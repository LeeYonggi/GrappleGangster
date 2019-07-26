#pragma once
#include "GameObject.h"
class Gun :
	public GameObject
{
public:
	Gun(Texture *texture, Timer *_timer) : GameObject(texture), timer(_timer) { }
	virtual ~Gun() { }

public:
	Timer* timer = nullptr;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void GunControll(Vector3 pos, Vector2 target);
	void GunShoot();
};

