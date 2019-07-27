#pragma once
#include "GameObject.h"

class Gun :
	public GameObject
{
public:
	Gun(Character *_owner, Texture *texture, float _time, float reloadTime) : 
		GameObject(texture), timer(Timer::AddTimer(_time)) 
	{
		maxTime = _time;
		maxReloadTime = reloadTime;
		reloadTimer = Timer::AddTimer(reloadTime);
		reloadTimer->Pause(true);
		owner = _owner;
	}
	virtual ~Gun() { }

private:
	GameUI* gage = nullptr;
	GameUI* gage2 = nullptr;
	Character* owner = nullptr;

public:
	Timer* reloadTimer = nullptr;
	Timer* timer = nullptr;
	float maxReloadTime = 0.0f;
	float maxTime = 0.0f;
	int bulletCount = 6;
	int reloadCount = 6;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void OnDisable();

public:
	void GunControll(Vector3 pos, Vector2 target);
	void MakeRifleBullet(Vector3 pos, GAMEOBJECT_STATE state, bool isInfluenceBackground, float speed);
	void Reload();

private:
	void GunShoot(Vector3 dis);
};

