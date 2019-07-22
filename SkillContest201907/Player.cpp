#include "DXUT.h"
#include "Player.h"

#include "MotionBlur.h"
#include "Bullet.h"

void Player::Init()
{
	mainTexture = Resources->LoadTexture("Character/test.png");
	motionBlur = OBJECTMANAGER->AddGameObject(new MotionBlur(this), GameObject::EFFECT);
	moveSpeed = 200;
	timer = Timer::AddTimer(1.0f);
}

void Player::Update()
{
	PlayerMove();
	PlayerAttack();
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
		timer->Reset(1.0f);
	}
}
