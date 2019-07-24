#include "DXUT.h"
#include "Player.h"

#include "MotionBlur.h"
#include "Bullet.h"
#include "Cartridge.h"
#include "Background.h"
#include "BackEffect.h"
#include "Ride.h"


void Player::Init()
{
	mainTexture = Resources->LoadTexture("Character/Player/body.png");
	motionBlur = OBJECTMANAGER->AddGameObject(new MotionBlur(this, MOTION_PLAYER), GameObject::EFFECT);
	moveSpeed = 350;
	timer = Timer::AddTimer(0.0f);
	pos.y = -100;

	background = dynamic_cast<Background*>(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());

	backEffect = new BackEffect(Resources->LoadTexture("Effect/BackEffect.png"));

	OBJECTMANAGER->AddGameObject(backEffect, GameObject::EFFECT);

	backEffect->SetActive(false);

	ride = new Ride(this, Ride::KOREA_BIKE);

	OBJECTMANAGER->AddGameObject(ride, GameObject::RIDE);
}

void Player::Update()
{
	PlayerMove();
	PlayerAttack();

	static bool f = false;

	if (INPUTMANAGER->IsKeyDown(VK_SPACE)) f = !f;

	if (f)
	{
		Timer::SetTimeScale(Lerp(Timer::GetTimeScale(), 0.1f, 0.05f));

		backEffect->SetActive(true);
	}
	else {
		Timer::SetTimeScale(Lerp(Timer::GetTimeScale(), 1.0f, 0.05f));

		backEffect->SetActive(false);
	}
}

void Player::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate);
}

void Player::Release()
{
	motionBlur->SetDestroy(true);
	Timer::RemoveTimer(timer);
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
	if (INPUTMANAGER->IsKeyPress(VK_LBUTTON) && timer->IsEnd)
	{
		Vector3 dir = ScreenToWorldCamera(INPUTMANAGER->GetMousePos());
		dir = GetVec3Distance(Vector3(pos.x, pos.y, 0), dir);

		Bullet::MakeRifleBullet(pos, dir, PLAYER_BULLET, true);

		timer->Reset(0.1f);
	}
}

