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

	attackTimer = Timer::AddTimer(2.0f);

	warringUI = new GameUI(0.6f, Resources->LoadTextures("UI/danger_effect/%d.png", 1, 5));

	OBJECTMANAGER->AddGameObject(warringUI, GameObject::UI);

	GAMEMANAGER->enemyCount += 1;
}

Enemy::~Enemy()
{
	Timer::RemoveTimer(attackTimer);
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	(this->*enemyFunc[enemyState])();
	
	EnemyWarring();

	if (enemyState == ENEMY_STATE::ENEMY_DIE) return;
	EnemyAttaked();
	
	pos.z = FixZToY(pos.y);
	gun->GunControll(pos, Vector2(player->GetPos()));
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

void Enemy::EnemyWarring()
{
	if (warringUI)
	{
		Vector2 ePos = WorldCameraToScreen(pos);
		if(ePos.x > 1280)
			warringUI->SetPos(Vector3(1230, ePos.y, 0));
		else if (ePos.x < 0)
		{
			warringUI->SetPos(Vector3(50, ePos.y, 0));
			warringUI->SetScale({-1, 1});
		}
		else
		{
			warringUI->SetDestroy(true);
			warringUI = nullptr;
		}
	}
}

void Enemy::EnemyAttaked()
{
	auto& bullets = OBJECTMANAGER->FindGameObjectsWithTag(GameObject::PLAYER_BULLET);

	for (auto* iter : bullets)
	{
		Vector3 dis = Vector3(pos.x, pos.y + 25, 0);
		dis.z = FixZToY(dis.y);

		bool isHit = GameObject::IsCircleCollision(iter->GetPos(), dis, 1, radius);

		if (!isHit) continue;

		hp -= 1;

		iter->SetDestroy(true);

		if (CharacterDie(static_cast<Bullet*>(iter)->GetMoveVector()) == true)
		{
			if (ride)
				ride->SetRider(nullptr);
		}

		CAMERAMANAGER->OneStopCamera(0.5f);

		break;
	}
}

bool Enemy::CharacterDie(Vector3 moveVec3)
{
	if (hp > 0) return false;

	enemyState = ENEMY_DIE;
	dieVec3 = moveVec3;
	D3DXVec3Normalize(&dieVec3, &dieVec3);

	diePosY = dieVec3.y * 100;
	dieVec3 *= 300;
	dieVec3.y += 400;
	gun->SetDestroy(true);

	GAMEMANAGER->enemyCount -= 1;

	return true;
}
