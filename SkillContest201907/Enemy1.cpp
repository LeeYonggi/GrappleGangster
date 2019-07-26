#include "DXUT.h"
#include "Enemy1.h"

#include "Ride.h"
#include "Gun.h"

Enemy1::Enemy1(Vector3 _targetPos, Vector3 spawnPos, Player* player)
	: Enemy(spawnPos, player, Resources->LoadTexture("Character/Enemy/Enemy_Die.png"))
{
	targetPos = _targetPos;

	ride = new Ride(this, Ride::JAPAN_BIKE1);
	OBJECTMANAGER->AddGameObject(ride, GameObject::RIDE);
	
	gun = ride->CreateGun();

	hp = 1;

	radius = 20;
}

Enemy1::~Enemy1()
{
}

void Enemy1::Init()
{
	enemyFunc[ENEMY_START] = &Enemy::EnemyStart;
	enemyFunc[ENEMY_MOVE] = &Enemy::EnemyMove;
	enemyFunc[ENEMY_DIE] = &Enemy::EnemyDie;

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
