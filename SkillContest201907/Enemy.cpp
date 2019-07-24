#include "DXUT.h"
#include "Enemy.h"

#include "Ride.h"

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

	if (enemyState != ENEMY_DIE)
		EnemyAttaked();
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


void Enemy::EnemyMove()
{
	sinCount += ELTime * (GetRandomNumberBetween(1, 4));
	cosCount += ELTime * (GetRandomNumberBetween(1, 4));

	pos.x += sin(sinCount) * 100.f * ELTime;
	pos.y += GetRandomNumberBetween(-20, 20) * ELTime;
}

void Enemy::EnemyDie()
{
	ride->SetRider(nullptr);
}

void Enemy::EnemyAttaked()
{
	auto bullets = OBJECTMANAGER->FindGameObjectsWithTag(GameObject::PLAYER_BULLET);

	for (auto iter = bullets.begin(); iter != bullets.end(); iter++)
	{
		bool isHit = GameObject::IsCircleCollision((*iter)->GetPos(), pos, (*iter)->GetRadius(), radius);

		if (isHit)
		{
			hp -= 1;
			(*iter)->SetDestroy(true);
		}
	}
}
