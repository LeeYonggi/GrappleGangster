#pragma once
#include "GameObject.h"

class Background;
class MotionBlur;
class BackEffect;
class Ride;
class Gun;
class Player :
	public GameObject
{
private:
	Vector3 moveVector = Vector3(0, 0, 0);
	MotionBlur* motionBlur = nullptr;
	Background *background;
	BackEffect* backEffect;
	Ride* ride = nullptr;

	float moveSpeed = 0.0f;
	float fireDelay = 0.7f;

	int nowGun = 0;

	vector<Gun*> gun;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void PlayerMove();
	void PlayerAttack();
};

