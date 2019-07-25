#include "DXUT.h"
#include "Player.h"

#include "MotionBlur.h"
#include "Bullet.h"
#include "Cartridge.h"
#include "Background.h"
#include "BackEffect.h"
#include "Ride.h"
#include "Gun.h"


void Player::Init()
{
	// 기본 이니셜라이즈
	mainTexture = Resources->LoadTexture("Character/Player/body.png");
	motionBlur = OBJECTMANAGER->AddGameObject(new MotionBlur(this, MOTION_PLAYER), GameObject::EFFECT);
	moveSpeed = 350;
	pos.y = -100;
	fireDelay = 0.7f;

	// 뒷배경
	background = dynamic_cast<Background*>(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());

	// 화면 뒤 이펙트
	backEffect = new BackEffect();

	OBJECTMANAGER->AddGameObject(backEffect, GameObject::EFFECT);

	backEffect->SetActive(false);

	// 오도방구
	ride = new Ride(this, Ride::KOREA_BIKE);

	OBJECTMANAGER->AddGameObject(ride, GameObject::RIDE);

	// 총
	gun.push_back(ride->CreateGun());

	nowGun = 0;
}

void Player::Update()
{
	PlayerMove();
	PlayerAttack();

	static bool f = false;

	/*if (INPUTMANAGER->IsKeyDown(VK_SPACE)) f = !f;

	if (f)
	{
		Timer::SetTimeScale(Lerp(Timer::GetTimeScale(), 0.1f, 0.05f));

		backEffect->SetActive(true);
	}
	else {
		Timer::SetTimeScale(Lerp(Timer::GetTimeScale(), 1.0f, 0.05f));

		backEffect->SetActive(false);
	}*/
}

void Player::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate);
}

void Player::Release()
{
	motionBlur->SetDestroy(true);
	gun.clear();
}

void Player::PlayerMove()
{
	moveVector.x = INPUTMANAGER->GetHorizontal();
	moveVector.y = INPUTMANAGER->GetVertical();

	if (moveVector.x < 0)
		moveVector.x = -0.7f;
	
	Vector3 nextPos = pos + moveVector * moveSpeed * ELTime;

	if (background->IsGroundCollision(Vector2(nextPos)) == Background::NONE)
		pos = nextPos;
	pos.x = min(max(pos.x, -SCREEN_X * 0.5f), SCREEN_X * 0.5f);
	pos.y = min(max(pos.y, -SCREEN_Y * 0.5f), SCREEN_Y * 0.5f);
	
	pos.z = pos.y + SCREEN_Y * 0.5f;
}

void Player::PlayerAttack()
{
	gun[nowGun]->GunControll(pos, Vector2(ScreenToWorldCamera(INPUTMANAGER->GetMousePos())));

	bool isKey = (INPUTMANAGER->IsKeyPress(VK_LBUTTON) || INPUTMANAGER->IsKeyDown(VK_LBUTTON));
	if (isKey && gun[nowGun]->timer->IsEnd)
	{
		Vector3 dir = ScreenToWorldCamera(INPUTMANAGER->GetMousePos());
		dir = GetVec3Distance(Vector3(pos.x, pos.y, 0), dir);

		Bullet::MakeRifleBullet(pos, dir, PLAYER_BULLET, true);

		gun[nowGun]->timer->Reset(fireDelay);
	}
}

