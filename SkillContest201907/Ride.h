#pragma once
#include "GameObject.h"


class Gun;
class MotionBlur;
class Background;
class ChargeUI;
class Ride :
	public GameObject
{
public:
	enum RIDE_STATE
	{
		KOREA_BIKE,
		JAPAN_BIKE1,
		JAPAN_BIKE2
	};

public:
	Ride(Character *_rider, RIDE_STATE rideState);
	virtual ~Ride();

private:
	Character *rider = nullptr;
	RIDE_STATE state;

	MotionBlur* motion = nullptr;
	Background* background = nullptr;
	ChargeUI* hpUI = nullptr;
	Timer* hitTimer = nullptr;

	Vector3 moveVector = Vector3(0, 0, 0);

	int hp = 3;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetRider(Character *value) { rider = value; }
	void RideAttacked();
	Gun* CreateGun();
	void Die();
	void RidePlayer();
	void SetHp(int value) { hp = value; }
};

