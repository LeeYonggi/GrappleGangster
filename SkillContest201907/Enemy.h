#pragma once
#include "GameObject.h"

class Ride;
class Gun;
class Player;
class Background;
class Enemy :
	public GameObject
{
	using EnemyFunc = void(Enemy::*)(void);
public:
	Enemy(Vector3 spawnPos, Player *_player, Texture* _dieTexture);
	virtual ~Enemy();

public:
	enum ENEMY_STATE
	{
		ENEMY_START,
		ENEMY_MOVE,
		ENEMY_DIE
	};

protected:
	EnemyFunc enemyFunc[3];
	ENEMY_STATE enemyState;

	Vector3 moveVector = Vector3(0, 0, 0);
	Vector3 targetPos = Vector3(0, 0, 0);
	Ride* ride = nullptr;
	Gun* gun = nullptr;
	Player* player;
	Texture* dieTexture = nullptr;
	Background* background = nullptr;

	float moveSpeed = 1.0f;
	float sinCount = 0.0f;
	float cosCount = 0.0f;

	int hp = 0;

	// 죽음 관련
	Vector3 dieVec3 = Vector3(0, 0, 0);
	float diePosY = 0;
	bool isDie = false;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void EnemyStart();
	void EnemyMove();
	void EnemyDie();

public:
	void EnemyAttaked();
	bool GetIsDie() { return isDie; }
};

