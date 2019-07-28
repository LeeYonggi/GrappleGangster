#include "DXUT.h"
#include "Boss.h"

#include "Gun.h"


Boss::Boss(Vector3 _targetPos, Vector3 spawnPos, Player* player)
	: Enemy(spawnPos, player, Resources->LoadTexture("Character/Boss/Body.png"))
{
	targetPos = _targetPos;

	ride = nullptr;

	hp = 80;

	radius = 150;
}

Boss::~Boss()
{
}

void Boss::Init()
{
	enemyFunc[ENEMY_START] = &Enemy::EnemyStart;
	enemyFunc[ENEMY_MOVE] = &Enemy::EnemyMove;
	enemyFunc[ENEMY_DIE] = &Enemy::BossDie;

	mainTexture = Resources->LoadTexture("Character/Boss/Body.png");

	moveSpeed = 500.0f;

	__super::Init();

	rightGun = new Gun(this, Resources->LoadTexture("Character/Boss/Gun.png"), 0.0f, 0.5f);

	OBJECTMANAGER->AddGameObject(rightGun, GameObject::GUN);

	leftGun = new Gun(this, Resources->LoadTexture("Character/Boss/Gun.png"), 0.0f, 2.0f);

	OBJECTMANAGER->AddGameObject(leftGun, GameObject::GUN);

	patternTimer = Timer::AddTimer(0.6f);
	rightTimer = Timer::AddTimer(1.0f);
	leftTimer = Timer::AddTimer(0.5f);

	pos.z = 180;

	isInfluenceGround = false;
}

void Boss::Update()
{
	__super::Update();

	if (enemyState == ENEMY_DIE) return;

	pos.z = 180;

	BossStateUpdate();
}

void Boss::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Boss::Release()
{
	Timer::RemoveTimer(patternTimer);
	Timer::RemoveTimer(rightTimer);
	Timer::RemoveTimer(leftTimer);

	rightGun->SetDestroy(true);
	leftGun->SetDestroy(true);
}

void Boss::BossStateUpdate()
{
	Vector3 rightDis = Vector3(-150, 120, 10);
	Vector3 leftDis = Vector3(0, 100, -10);
	Vector3 tempPos = pos;
	tempPos.z = FixZToY(pos.y);
	switch (pattern)
	{
	case Boss::IDLE:
		rightGun->GunControll(pos + rightDis, Vector2(pos.x - 160, pos.y + 120));
		leftGun->GunControll(pos + leftDis, Vector2(pos.x - 10, pos.y + 100));

		if (enemyState == ENEMY_MOVE)
			ChangePattern();
		break;
	case Boss::CONTINUITY_SHOOT:
		rightGun->GunControll(pos + rightDis, Vector2(player->GetPos()));
		leftGun->GunControll(pos + leftDis, Vector2(player->GetPos()));

		if (rightTimer->IsEnd)
		{
			rightGun->GunShoot(GameObject::ENEMY_BULLET, player->GetPos(), 700);
			rightTimer->Reset(1.0f);
		}
		if (leftTimer->IsEnd)
		{
			leftGun->GunShoot(GameObject::ENEMY_BULLET, player->GetPos(), 700);
			leftTimer->Reset(1.0f);
		}

		if (patternTimer->IsEnd)
			ChangePattern();

		break;
	case Boss::CREATE_ENEMY:
		rightGun->GunControll(pos + rightDis, Vector2(player->GetPos()));
		leftGun->GunControll(pos + leftDis, Vector2(player->GetPos()));

		if (patternTimer->IsEnd)
			ChangePattern();

		break;
	case Boss::FLY_SHOOT:
		rightGun->GunControll(pos + rightDis, Vector2(0, SCREEN_Y * 0.5f));
		leftGun->GunControll(pos + leftDis, Vector2(0, SCREEN_Y * 0.5f));

		if (rightTimer->IsEnd)
		{
			rightGun->GunShoot(GameObject::ENEMY_BULLET, 700);
			rightTimer->Reset(0.2f);
		}
		if (leftTimer->IsEnd)
		{
			leftGun->GunShoot(GameObject::ENEMY_BULLET, 700);
			leftTimer->Reset(0.2f);
		}

		if (rightGun->bulletCount == 0)
		{
			for (int x = 1; x < 9; x++)
			{
				for (int y = 1; y < 5; y++)
				{
					Vector3 targetPos = Vector3(-SCREEN_X * 0.5f, -SCREEN_Y * 0.5f, 0);
					Vector3 bulletPos = Vector3(-SCREEN_X * 0.5f, SCREEN_Y * 0.5f, 0);
					if (y % 2 + x % 2 == 1) continue;
					targetPos.x += 100 * x;
					targetPos.y += 60 * y;
					targetPos.z = FixZToY(targetPos.y);
					bulletPos.x = targetPos.x + 100;
					Gun::MakeRifleBullet(bulletPos, targetPos, ENEMY_BULLET, false, 800);
				}
			}
			ChangePattern();
		}

		break;
	default:
		break;
	}
}


void Boss::ChangePattern()
{
	PATTERN_STATE nextPattern = (PATTERN_STATE)GetRandomNumberBetween(1, 3);
	if (pattern == nextPattern)
		ChangePattern();
	pattern = nextPattern;
	leftGun->reloadCount = 15;
	rightGun->reloadCount = 15;

	switch (pattern)
	{
	case Boss::IDLE:
		break;
	case Boss::CONTINUITY_SHOOT:
		rightTimer->Reset(1.0f);
		leftTimer->Reset(0.5f);
		patternTimer->Reset(13.0f);

		rightGun->Reload();
		leftGun->Reload();
		break;
	case Boss::CREATE_ENEMY:
		patternTimer->Reset(10.0f);

		GAMEMANAGER->CreateEnemy1();
		GAMEMANAGER->CreateEnemy1();
		GAMEMANAGER->CreateEnemy2();
		GAMEMANAGER->CreateEnemy2();
		GAMEMANAGER->CreateEnemy1();

		break;
	case Boss::FLY_SHOOT:
		rightTimer->Reset(0.4f);
		leftTimer->Reset(0.2f);

		leftGun->bulletCount = 15;
		rightGun->bulletCount = 15;

		break;
	default:
		break;
	}
}

