#include "DXUT.h"
#include "Enemy1.h"

Enemy1::Enemy1(Vector3 _targetPos, Vector3 spawnPos)
	: Enemy(spawnPos)
{
	targetPos = _targetPos;
}

Enemy1::~Enemy1()
{
}

void Enemy1::Init()
{
	enemyFunc[ENEMY_START] = &Enemy::EnemyStart;
	enemyFunc[ENEMY_MOVE] = &Enemy::EnemyMove;

	mainTexture = Resources->LoadTexture("Character/Enemy.png");

	moveSpeed = 200.0f;

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
