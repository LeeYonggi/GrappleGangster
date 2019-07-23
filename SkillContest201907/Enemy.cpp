#include "DXUT.h"
#include "Enemy.h"


Enemy::Enemy(Vector3 spawnPos)
{
	enemyState = ENEMY_START;
	pos = spawnPos;
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

	pos.z = FixZToY(pos.y);
}

void Enemy::Render()
{
}

void Enemy::Release()
{
}

void Enemy::EnemyStart()
{
	moveVector = GetVec3Distance(pos, targetPos);

	pos += moveVector * ELTime * moveSpeed;

	Vector2 length = targetPos - pos;

	if (D3DXVec2Length(&length) < 3.0f)
		enemyState = ENEMY_STATE::ENEMY_MOVE;
}

class Random
{
public:
	static int Range(int min, int max) { return GetRandomNumberBetween(min, max); }
};

void Enemy::EnemyMove()
{
	sinCount += ELTime * (Random::Range(1, 4));
	cosCount += ELTime * (Random::Range(1, 4));

	pos.x += sin(sinCount) * 0.1f;
	pos.y += cos(cosCount) * 0.05f;
}

void Enemy::EnemyDie()
{

}
