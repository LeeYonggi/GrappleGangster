#include "DXUT.h"
#include "Ride.h"

#include "GameObject.h"
#include "Gun.h"
#include "MotionBlur.h"
#include "Background.h"

Ride::Ride(GameObject* _rider, RIDE_STATE rideState)
{
	rider = _rider;
	state = rideState;
	background = dynamic_cast<Background*>(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());
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
			motion->SetTargetState(MOTION_PLAYER);
		else
			motion->SetTargetState(MOTION_MANAGED);
	}
	else
	{
		moveVector = Vector3(-background->GetMoveSpeed() * 0.5f, 0, 0);
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

Gun* Ride::CreateGun()
{
	Gun* gun = nullptr;

	switch (state)
	{
	case Ride::KOREA_BIKE:
		gun = new Gun(Resources->LoadTexture("Gun/HandGun.png"), Timer::AddTimer(0.7f));
		break;
	case Ride::JAPAN_BIKE1:
		gun = new Gun(Resources->LoadTexture("Gun/HandGun.png"), Timer::AddTimer(0.7f));
		break;
	case Ride::JAPAN_BIKE2:
		gun = new Gun(Resources->LoadTexture("Gun/RifleGun.png"), Timer::AddTimer(0.2f));
		break;
	default:
		break;
	}

	OBJECTMANAGER->AddGameObject(gun, GameObject::GUN);
	return gun;
}
