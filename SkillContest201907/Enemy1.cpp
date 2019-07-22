#include "DXUT.h"
#include "Enemy1.h"

Enemy1::Enemy1()
{
}

Enemy1::~Enemy1()
{
}

void Enemy1::Init()
{
	enemyFunc[ENEMY_START] = &Enemy::EnemyRightStart;

	mainTexture = Resources->LoadTexture("Character/test.png");
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
