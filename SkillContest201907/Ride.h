#pragma once
#include "GameObject.h"


class Gun;
class MotionBlur;
class Background;
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
	Ride(GameObject *_rider, RIDE_STATE rideState);
	virtual ~Ride();

private:
	GameObject *rider = nullptr;
	RIDE_STATE state;

	MotionBlur* motion = nullptr;
	Background* background = nullptr;

	Vector3 moveVector = Vector3(0, 0, 0);

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetRider(GameObject *value) { rider = value; }
	Gun* CreateGun();
};

