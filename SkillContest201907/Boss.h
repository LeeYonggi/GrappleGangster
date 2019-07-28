#pragma once
#include "Enemy.h"


class Boss :
	public Enemy
{
public:
	Boss(Vector3 _targetPos, Vector3 spawnPos, Player* player);
	virtual ~Boss();

private:
	enum PATTERN_STATE
	{
		IDLE,
		CONTINUITY_SHOOT,
		CREATE_ENEMY,
		FLY_SHOOT
	};

	PATTERN_STATE pattern = IDLE;

	Gun* rightGun = nullptr;
	Gun* leftGun = nullptr;
	Vector3 target = Vector3(0, 0, 0);

	Timer* patternTimer = nullptr;
	Timer* rightTimer = nullptr;
	Timer* leftTimer = nullptr;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void BossStateUpdate();

public:
	void ChangePattern();

};

