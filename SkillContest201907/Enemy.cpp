#include "DXUT.h"
#include "Enemy.h"

#include "Ride.h"
#include "Gun.h"
#include "Player.h"
#include "Bullet.h"
#include "Background.h"
#include "AnimeEffect.h"

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

	hitTimer = Timer::AddTimer(0.0f);
}

Enemy::~Enemy()
{
	Timer::RemoveTimer(attackTimer);
	Timer::RemoveTimer(hitTimer);
	Timer::RemoveTimer(dieTimer);
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	(this->*enemyFunc[enemyState])();
	
	EnemyWarring();

	if (hitTimer->IsEnd)
		color = Color(1, 1, 1, 1);

	if (enemyState == ENEMY_STATE::ENEMY_DIE) return;

	if(pos.x < SCREEN_X * 0.5f && pos.x > -SCREEN_X * 0.5f)
		EnemyAttaked();
	
	if(isInfluenceGround)
		pos.z = FixZToY(pos.y);

	if(gun)
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

	if (diePosY < pos.y || dieVec3.y > 0 || (GAMEMANAGER->stage != STAGE_1 && pos.y > -90))
	{
		pos += dieVec3 * ELTime;

		dieVec3.y -= 1000 * ELTime;

		rotate += GetRandomNumberBetween(500, 1000) * ELTime;
	}
	else if (GAMEMANAGER->stage != STAGE_1)
	{
		vector<Texture*> anime = Resources->LoadTextures("Effect/splash/%d.png", 1, 9);

		AnimeEffect* effect = new AnimeEffect(0.8f, anime);

		OBJECTMANAGER->AddGameObject(effect, GAMEOBJECT_STATE::EFFECT);

		effect->SetScale(Vector2(2, 2));

		effect->SetPos(pos);

		SetDestroy(true);
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

void Enemy::EnemyMoveCollision()
{
	Background::GROUND_COLLISION collision = background->IsGroundCollision(Vector2(pos));

	if (collision == Background::UNACCESS_UP)
		pos = Vector3(pos.x, pos.y + 10, pos.z);
	else if(collision == Background::UNACCESS_DOWN)
		pos = Vector3(pos.x, pos.y - 10, pos.z);
}

void Enemy::BossDie()
{
	hitTimer->SetIsInfluenceOfTimeScale(false);
	dieTimer->SetIsInfluenceOfTimeScale(false);
	Timer::SetTimeScale(0.0f);
	if (hitTimer->IsEnd)
	{
		hitTimer->Reset(0.1f);

		Vector3 effectPos = pos;

		effectPos.x += GetRandomNumberBetween(-200, 200);
		effectPos.y += GetRandomNumberBetween(-200, 200);
		effectPos.z = FixZToY(pos.y);

		vector<Texture*> anime = Resources->LoadTextures("Effect/explosion/explosion_%d.png", 1, 9);

		AnimeEffect* effect = new AnimeEffect(0.8f, anime);

		OBJECTMANAGER->AddGameObject(effect, GAMEOBJECT_STATE::EFFECT);

		effect->SetScale(Vector2(2, 2));

		effect->SetPos(effectPos);

		color = Color(1, 1, 1, 1);
	}
	if (dieTimer->IsEnd)
	{
		SetDestroy(true);

		vector<Texture*> anime = Resources->LoadTextures("Effect/explosion/explosion_%d.png", 1, 9);

		AnimeEffect* effect = new AnimeEffect(0.8f, anime);

		OBJECTMANAGER->AddGameObject(effect, GAMEOBJECT_STATE::EFFECT);

		effect->SetScale(Vector2(2, 2));

		effect->SetPos(pos);

		effect->SetScale({ 5, 5 });

		auto enemy = OBJECTMANAGER->FindGameObjectsWithTag(ENEMY);

		for (auto iter : enemy)
		{
			static_cast<Enemy*>(iter)->CharacterDie(Vector3(100, 100, 0));
			static_cast<Enemy*>(iter)->ride = nullptr;
		}

		GAMEMANAGER->ChangeStage();
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
		hitTimer->Reset(0.3f);
		color = Color(1, 0, 0, 1);

		if (hp < 1)
		{
			CharacterDie(static_cast<Bullet*>(iter)->GetMoveVector());
			if (ride)
				ride->SetRider(nullptr);
		}

		CAMERAMANAGER->OneStopCamera(0.5f);

		break;
	}
}

void Enemy::CharacterDie(Vector3 moveVec3)
{
	enemyState = ENEMY_DIE;
	dieVec3 = moveVec3;
	D3DXVec3Normalize(&dieVec3, &dieVec3);

	diePosY = dieVec3.y * 100;
	dieVec3 *= 300;
	dieVec3.y += 400;
	if(gun)
		gun->SetDestroy(true);
	
	if(warringUI)
		warringUI->SetDestroy(true);

	dieTimer = Timer::AddTimer(3.0f);

	GAMEMANAGER->enemyCount -= 1;
}
