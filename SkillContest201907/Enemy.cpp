#include "DXUT.h"
#include "Enemy.h"

Enemy::Enemy()
{
	enemyState = ENEMY_START;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	(this->*enemyFunc[enemyState])();
}

void Enemy::Render()
{
}

void Enemy::Release()
{
}

void Enemy::EnemyRightStart()
{
	pos = {500, -300, 0};
}

void Enemy::EnemyDie()
{

}
