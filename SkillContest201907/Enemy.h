#pragma once
#include "GameObject.h"

class Enemy :
	public GameObject
{
	using EnemyFunc = void(Enemy::*)(void);
public:
	Enemy();
	virtual ~Enemy();

public:
	enum ENEMY_STATE
	{
		ENEMY_START,
		ENEMY_MOVE,
		ENEMY_ATTACK
	};

protected:
	EnemyFunc enemyFunc[3];
	ENEMY_STATE enemyState;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void EnemyRightStart();
	void EnemyDie();
};

