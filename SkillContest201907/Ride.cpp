#include "DXUT.h"
#include "Ride.h"

#include "GameObject.h"
#include "Gun.h"
#include "MotionBlur.h"
#include "Background.h"

Ride::Ride(Character* _rider, RIDE_STATE rideState)
{
	rider = _rider;
	state = rideState;

	background = dynamic_cast<Background*>(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());

	radius = 40.0f;
}

Ride::~Ride()
{
}

void Ride::Init()
{
	motion = new MotionBlur(this, MOTION_MANAGED);

	switch (state)
	{
	case Ride::KOREA_BIKE:
		mainTexture = Resources->LoadTexture("Ride/Korea/Bike.png");
		break;
	case Ride::JAPAN_BIKE1:
		mainTexture = Resources->LoadTexture("Ride/Japan/Bike1.png");
		break;
	case Ride::JAPAN_BIKE2:
		mainTexture = Resources->LoadTexture("Ride/Japan/Bike2.png");
		break;
	default:
		break;
	}

	OBJECTMANAGER->AddGameObject(motion, GameObject::EFFECT);
}

void Ride::Update()
{
	if (rider)
	{
		Vector3 riderPos = rider->GetPos();

		pos = riderPos;
		
		motion->SetActive(true);

		if (rider->GetTag() == PLAYER)
		{
			motion->SetTargetState(MOTION_PLAYER);
			radius = 20;
		}
		else
			motion->SetTargetState(MOTION_MANAGED);

		RideAttacked();
	}
	else
	{
		RidePlayer();
		moveVector = Vector3(-background->GetMoveSpeed() * 0.1f, 0, 0);
		motion->SetActive(false);
		pos += moveVector * ELTime;
	}
}

void Ride::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Ride::Release()
{
	motion->SetDestroy(true);
}

void Ride::RideAttacked()
{
	list<GameObject*> bullets;
	
	if (rider->GetTag() == GameObject::PLAYER)
		bullets = OBJECTMANAGER->FindGameObjectsWithTag(GameObject::ENEMY_BULLET);
	else if (rider->GetTag() == GameObject::ENEMY)
		bullets = OBJECTMANAGER->FindGameObjectsWithTag(GameObject::PLAYER_BULLET);

	for (auto iter : bullets)
	{
		Vector3 dis = Vector3(0, -20, -20);

		if (!GameObject::IsCircleCollision((iter)->GetPos(), pos + dis, (iter)->GetRadius(), radius))
			continue;

		if (rider->GetTag() == GameObject::ENEMY)
			CAMERAMANAGER->OneStopCamera(0.15f);

		(iter)->SetDestroy(true);
		hp -= 1;
		
		if (hp > 0)
			continue;

		Die();
	}
}

Gun* Ride::CreateGun()
{
	Gun* gun = nullptr;

	switch (state)
	{
	case Ride::KOREA_BIKE:
		gun = new Gun(rider, Resources->LoadTexture("Gun/HandGun.png"), 0.7f, 1.0f);
		break;
	case Ride::JAPAN_BIKE1:
		gun = new Gun(rider, Resources->LoadTexture("Gun/HandGun.png"), 0.7f, 2.0f);
		break;
	case Ride::JAPAN_BIKE2:
		gun = new Gun(rider, Resources->LoadTexture("Gun/RifleGun.png"), 0.2f, 2.0f);
		break;
	default:
		break;
	}

	OBJECTMANAGER->AddGameObject(gun, GameObject::GUN);
	return gun;
}

void Ride::Die()
{
	if (rider)
	{
		rider->SetHp(0);

		rider->CharacterDie(Vector3(100, 100, 0));

		SetDestroy(true);

		vector<Texture*> anime = Resources->LoadTextures("Effect/explosion/explosion_%d.png", 1, 9);

		AnimeEffect* effect = new AnimeEffect(0.6f, anime);

		effect->SetScale(Vector2(2, 2));

		effect->SetPos(pos);

		OBJECTMANAGER->AddGameObject(effect, GameObject::EFFECT);
		CAMERAMANAGER->OneStopCamera(0.5f);
	}
}

void Ride::RidePlayer()
{
	Player* player = Player::mainPlayer;

	if (player->IsRideOn()) return;

	Vector3 dis = Vector3(0, -20, -20);

	if (GameObject::IsCircleCollision(player->GetPos(), pos + dis, player->GetRadius(), radius))
	{
		player->SetRide(this);
		rider = player;
		if (state == JAPAN_BIKE2)
		{
			player->gun[1] = CreateGun();
			player->gun[1]->SetActive(false);
			player->gun[1]->reloadCount = 10;
		}
	}
}
