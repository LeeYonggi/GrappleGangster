#pragma once
#include "Character.h"

class Background;
class MotionBlur;
class BackEffect;
class Ride;
class Gun;
class Player :
	public Character
{
private:
	Vector3 moveVector = Vector3(0, 0, 0);
	MotionBlur* motionBlur = nullptr;
	Background *background;
	BackEffect* backEffect;
	Ride* ride = nullptr;
	Timer* jumpTimer = nullptr;
	vector<Texture*> jumpAnime;
	Vector3 velocity;

	float moveSpeed = 0.0f;
	float fireDelay = 0.7f;

	int nowGun = 0;
	bool isRideOn = true;

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
	virtual bool CharacterDie(Vector3 moveVec3) override;

public:
	void PlayerMove();
	void PlayerAttack();
	void PlayerTimeStop();
	void PlayerJump();
	void PlayerJumpUpdate();


public:
	static Player* mainPlayer;
};

