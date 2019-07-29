#pragma once
#include "Character.h"

class Background;
class MotionBlur;
class BackEffect;
class Ride;
class Gun;
class ChargeUI;
class Player :
	public Character
{
private:
	Vector3 moveVector = Vector3(0, 0, 0);
	MotionBlur* motionBlur = nullptr;
	Background *background;
	BackEffect* backEffect;
	Ride* ride = nullptr;
	vector<Texture*> jumpAnime;
	Vector3 velocity;
	GameUI* reload = nullptr;
	ChargeUI* timeUI = nullptr;

	Timer* timeTimer = nullptr;
	Timer* jumpTimer = nullptr;

	float moveSpeed = 0.0f;
	float fireDelay = 0.7f;

	int nowGun = 0;
	int timeCharge = 5;
	bool isRideOn = true;

public:
	vector<Gun*> gun;

public:
	Player();
	~Player();

	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetRide(Ride* other) 
	{
		ride = other;
		isRideOn = true;
		jumpTimer->Reset(0.4);
	}
	bool IsRideOn() { return isRideOn; }

public:
	virtual void CharacterDie(Vector3 moveVec3) override;

public:
	void PlayerMove();
	void PlayerAttack();
	void PlayerTimeStop();
	void PlayerJump();
	void PlayerJumpUpdate();
	void PlayerGun();
	void Reload();


public:
	static Player* mainPlayer;
};

