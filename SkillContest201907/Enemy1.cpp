#include "DXUT.h"
#include "Enemy1.h"

#include "Ride.h"

Enemy1::Enemy1(Vector3 _targetPos, Vector3 spawnPos)
	: Enemy(spawnPos)
{
	targetPos = _targetPos;

	ride = new Ride(this, Ride::JAPAN_BIKE1);
	OBJECTMANAGER->AddGameObject(ride, GameObject::RIDE);

	hp = 3;

	radius = 50;
}

Enemy1::~Enemy1()
{
}

void Enemy1::Init()
{
	enemyFunc[ENEMY_START] = &Enemy::EnemyStart;
	enemyFunc[ENEMY_MOVE] = &Enemy::EnemyMove;

	mainTexture = Resources->LoadTexture("Character/Enemy/Enemy.png");

	moveSpeed = 500.0f;

	__super::Init();
}

void Enemy1::Update()
{
	__super::Update();
}

void Enemy1::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Enemy1::Release()
{
}
