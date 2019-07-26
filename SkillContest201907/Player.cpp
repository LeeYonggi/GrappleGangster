#include "DXUT.h"
#include "Player.h"

#include "MotionBlur.h"
#include "Bullet.h"
#include "Cartridge.h"
#include "Background.h"
#include "BackEffect.h"
#include "Ride.h"
#include "Gun.h"

Player* Player::mainPlayer = nullptr;


Player::Player()
{
	if (mainPlayer == nullptr)
		mainPlayer = this;
}

Player::~Player()
{
	if (mainPlayer == this)
		mainPlayer = nullptr;
}

void Player::Init()
{
	// 기본 이니셜라이즈
	mainTexture = Resources->LoadTexture("Character/Player/body.png");
	motionBlur = OBJECTMANAGER->AddGameObject(new MotionBlur(this, MOTION_PLAYER), GameObject::EFFECT);
	moveSpeed = 350;
	pos.y = -100;
	fireDelay = 0.7f;
	jumpTimer = Timer::AddTimer(0.0f);
	jumpAnime = Resources->LoadTextures("Character/Player/character_jump/%d.png", 1, 4);
	velocity = Vector3(0, 0, 0);

	// 뒷배경
	background = dynamic_cast<Background*>(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());

	// 화면 뒤 이펙트
	backEffect = new BackEffect();

	OBJECTMANAGER->AddGameObject(backEffect, GameObject::EFFECT);

	backEffect->SetActive(true);

	// 오도방구
	ride = new Ride(this, Ride::KOREA_BIKE);

	OBJECTMANAGER->AddGameObject(ride, GameObject::RIDE);

	// 총
	gun.push_back(ride->CreateGun());
	gun.push_back(nullptr);

	nowGun = 0;

	// UI
	reload = new GameUI(Resources->LoadTexture("UI/ReloadGage/R.png"));

	OBJECTMANAGER->AddGameObject(reload, GameObject::EFFECT);

	reload->SetActive(false);
}

void Player::Update()
{
	PlayerMove();
	PlayerAttack();
	PlayerTimeStop();

	if (INPUTMANAGER->IsKeyDown(VK_SPACE))
		PlayerJump();
	if (ride == nullptr)
		PlayerJumpUpdate();
}

void Player::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate);
}

void Player::Release()
{
	motionBlur->SetDestroy(true);
	Timer::RemoveTimer(jumpTimer);
	gun.clear();
}

bool Player::CharacterDie(Vector3 moveVec3)
{
	return false;
}

void Player::PlayerMove()
{
	moveVector.x = INPUTMANAGER->GetHorizontal();
	if (ride == nullptr)
		moveVector.y = 0;
	else
		moveVector.y = INPUTMANAGER->GetVertical();

	if (moveVector.x < 0)
		moveVector.x = -0.7f;
	
	Vector3 nextPos = pos + moveVector * moveSpeed * ELTime;

	if (background->IsGroundCollision(Vector2(nextPos)) == Background::NONE 
		|| ride == nullptr)
		pos = nextPos;
	pos.x = min(max(pos.x, -SCREEN_X * 0.5f), SCREEN_X * 0.5f);
	pos.y = min(max(pos.y, -SCREEN_Y * 0.5f), SCREEN_Y * 0.5f);
	
	pos.z = FixZToY(pos.y);

	if (jumpTimer->IsEnd)
		mainTexture = Resources->LoadTexture("Character/Player/body.png");
	else if(isRideOn)
	{
		int nowTexture = (jumpTimer->GetAnyTime() / 0.6f) * (jumpAnime.size() - 1);
		mainTexture = jumpAnime[nowTexture];
	}
}

void Player::PlayerAttack()
{
	PlayerGun();
	if (gun[nowGun] == nullptr) return;
	gun[nowGun]->GunControll(pos, Vector2(ScreenToWorldCamera(INPUTMANAGER->GetMousePos())));

	bool isKey = (INPUTMANAGER->IsKeyPress(VK_LBUTTON) || INPUTMANAGER->IsKeyDown(VK_LBUTTON));
	gun[nowGun]->timer->SetIsInfluenceOfTimeScale(false);
	if (isKey && gun[nowGun]->timer->IsEnd)
	{
		Vector3 dir = ScreenToWorldCamera(INPUTMANAGER->GetMousePos());
		dir = GetVec3Distance(Vector3(pos.x, pos.y, 0), dir);

		gun[nowGun]->MakeRifleBullet(pos, PLAYER_BULLET, true, 1000);
		gun[nowGun]->timer->Reset(gun[nowGun]->maxTime);
	}
}

void Player::PlayerTimeStop()
{
	static bool isTimeStop = false;

	isTimeStop = INPUTMANAGER->IsKeyPress(VK_SHIFT);

	if (isTimeStop == true)
	{
		Timer::SetTimeScale(Lerp(Timer::GetTimeScale(), 0.1f, 0.05f));

		backEffect->SetColor(Color(1, 1, 1, Lerp(backEffect->GetColor().a, 1.0f, 0.25f)));
	}

	if (isTimeStop == false)
	{
		Timer::SetTimeScale(Lerp(Timer::GetTimeScale(), 1.0f, 0.05f));

		backEffect->SetColor(Color(1, 1, 1, Lerp(backEffect->GetColor().a, 0.0f, 0.25f)));
	}
}

void Player::PlayerJump()
{
	if (ride == nullptr) return;

	ride->SetRider(nullptr);
	ride = nullptr;
	isRideOn = false;

	jumpTimer->Reset(0.4f);

	pos.y += 20;

	velocity.y = 400;
}

void Player::PlayerJumpUpdate()
{
	int nowTexture = ((0.4f - jumpTimer->GetAnyTime()) / 0.4f) * (jumpAnime.size() - 1);
	mainTexture = jumpAnime[nowTexture];

	velocity.y -= 500 * ELTime;

	pos += velocity * ELTime;
}

void Player::PlayerGun()
{
	if (INPUTMANAGER->IsKeyDown('1'))
	{
		nowGun = 0;
		gun[nowGun]->SetActive(true);
		if(gun[1] != nullptr)
			gun[1]->SetActive(false);
	}
	if (INPUTMANAGER->IsKeyDown('2') && gun[1] != nullptr)
	{
		nowGun = 1;
		gun[0]->SetActive(false);
		gun[nowGun]->SetActive(true);
	}

	if (gun[nowGun] == nullptr) return;
	if (nowGun == 1 && gun[nowGun]->bulletCount < 1)
	{
		gun[nowGun]->Reload();
		return;
	}
	else if (INPUTMANAGER->IsKeyDown('R'))
	{
		gun[nowGun]->Reload();
	}
	if (gun[nowGun]->bulletCount < 1 &&
		gun[nowGun]->reloadTimer->GetAnyTime() == gun[nowGun]->maxReloadTime)
	{
		reload->SetActive(true);

		Vector2 uiPos = WorldCameraToScreen(pos);

		reload->SetPos(Vector3(uiPos.x + 60, uiPos.y - 60, 0));
	}
	else
		reload->SetActive(false);
}

