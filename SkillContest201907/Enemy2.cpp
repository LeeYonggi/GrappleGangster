#include "DXUT.h"
#include "Enemy2.h"

#include "Ride.h"
#include "Gun.h"

Enemy2::Enemy2(Vector3 targetPos, Vector3 spawnPos, Player *player)
	:Enemy(spawnPos, player, Resources->LoadTexture("Character/Enemy2/Enemy2_Die.png"))
{
	this->targetPos = targetPos;

	ride = new Ride(this, Ride::JAPAN_BIKE2);
	OBJECTMANAGER->AddGameObject(ride, GameObject::RIDE);

	gun = ride->CreateGun();

	radius = 20;
}

Enemy2::~Enemy2()
{
}

void Enemy2::Init()
{
	enemyFunc[ENEMY_START] = &Enemy::EnemyStart;
	enemyFunc[ENEMY_MOVE] = &Enemy::EnemyMove;
	enemyFunc[ENEMY_DIE] = &Enemy::EnemyDie;

	mainTexture = Resources->LoadTexture("Character/Enemy2/Enemy2.png");

	hp = 1;

	moveSpeed = 300.0f;

	gun->reloadCount = 5;
	gun->bulletCount = 5;

	__super::Init();
}

void Enemy2::Update()
{
	__super::Update();

	if (enemyState != ENEMY_MOVE) return;

	if (gun->timer->IsEnd)
	{
		gun->MakeRifleBullet(pos, GameObject::ENEMY_BULLET, true, 600);
		gun->timer->Reset(0.6f);
	}
	if (gun->bulletCount < 1)
		gun->Reload();
}

void Enemy2::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Enemy2::Release()
{
}
