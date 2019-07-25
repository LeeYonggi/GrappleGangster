#include "DXUT.h"
#include "Enemy.h"

#include "Ride.h"
#include "Gun.h"
#include "Player.h"
#include "Bullet.h"
#include "Background.h"

Enemy::Enemy(Vector3 spawnPos, Player* _player, Texture* _dieTexture)
{
	enemyState = ENEMY_START;
	pos = spawnPos;
	player = _player;
	dieTexture = _dieTexture;
	background = dynamic_cast<Background*>(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());
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
	
	if (enemyState != ENEMY_DIE)
	{
		pos.z = FixZToY(pos.y);
		gun->GunControll(pos, Vector2(player->GetPos()));
		EnemyAttaked();
	}
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

	mainTexture = dieTexture;

	if (diePosY < pos.y || dieVec3.y > 0)
	{
		pos += dieVec3 * ELTime;

		dieVec3.y -= 1000 * ELTime;

		rotate += GetRandomNumberBetween(500, 1000) * ELTime;
	}
	else
	{
		pos += Vector3(-background->GetMoveSpeed(), 0, 0) * ELTime;
		pos.z = 500;
	}

	if (pos.x < -SCREEN_X * 0.6f)
	{
		isDie = true;
		SetDestroy(true);
	}
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

			if (hp < 1)
			{
				enemyState = ENEMY_DIE;
				dieVec3 = dynamic_cast<Bullet*>((*iter))->GetMoveVector();
				D3DXVec3Normalize(&dieVec3, &dieVec3);
				
				diePosY = dieVec3.y * 100;
				dieVec3 *= 300;
				dieVec3.y += 400;
				gun->SetDestroy(true);

				CAMERAMANAGER->OneStopCamera();
				break;
			}
		}
	}
}
