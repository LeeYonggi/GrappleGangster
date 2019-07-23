#include "DXUT.h"
#include "Player.h"

#include "MotionBlur.h"
#include "Bullet.h"
#include "Cartridge.h"
#include "Background.h"
#include "BackEffect.h"


void Player::Init()
{
	mainTexture = Resources->LoadTexture("Character/Bike.png");
	motionBlur = OBJECTMANAGER->AddGameObject(new MotionBlur(this), GameObject::EFFECT);
	moveSpeed = 350;
	timer = Timer::AddTimer(1.0f);
	pos.y = -100;
	background = dynamic_cast<Background*>(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());

	backEffect = new BackEffect(Resources->LoadTexture("Effect/BackEffect.png"));

	OBJECTMANAGER->AddGameObject(backEffect, GameObject::EFFECT);

	backEffect->SetActive(false);
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
	
	pos += moveVector * moveSpeed * ELTime;

	pos.x = min(max(pos.x, -SCREEN_X * 0.5f), SCREEN_X * 0.5f);
	pos.y = min(max(pos.y, -SCREEN_Y * 0.5f), SCREEN_Y * 0.5f);
	
	pos.z = pos.y + SCREEN_Y * 0.5f;
}

void Player::PlayerAttack()
{
	if (INPUTMANAGER->IsKeyDown(VK_LBUTTON) && timer->IsEnd)
	{
		Vector3 dir = ScreenToWorldCamera(INPUTMANAGER->GetMousePos());
		dir = GetVec3Distance(Vector3(pos.x, pos.y, 0), dir);

		Bullet* bullet = new Bullet(Resources->LoadTexture("Bullet/Player_Bullet.png"),
			dir * 1000);

		bullet->SetPos(pos);

		OBJECTMANAGER->AddGameObject(bullet, GameObject::PLAYER_BULLET);

		Cartridge* cartridge = new Cartridge(pos, background);

		OBJECTMANAGER->AddGameObject(cartridge, GameObject::EFFECT);


		timer->Reset(1.0f);
	}
}
