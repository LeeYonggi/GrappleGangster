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
		gun = new Gun(Resources->LoadTexture("Gun/HandGun.png"));

		break;
	case Ride::JAPAN_BIKE1:
		mainTexture = Resources->LoadTexture("Ride/Japan/Bike1.png");
		gun = new Gun(Resources->LoadTexture("Gun/HandGun.png"));
		break;
	case Ride::JAPAN_BIKE2:
		mainTexture = Resources->LoadTexture("Ride/Japan/Bike2.png");
		gun = new Gun(Resources->LoadTexture("Gun/RifleGun.png"));
		break;
	default:
		break;
	}

	OBJECTMANAGER->AddGameObject(motion, GameObject::EFFECT);
	OBJECTMANAGER->AddGameObject(gun, GameObject::GUN);
}

void Ride::Update()
{
	if (rider)
	{
		Vector3 riderPos = rider->GetPos();

		pos = riderPos + Vector3(0, 0, -1);
		
		motion->SetActive(true);

		if (rider->GetTag() == PLAYER)
			motion->SetTargetState(MOTION_PLAYER);
		else
			motion->SetTargetState(MOTION_MANAGED);
	}
	else
	{
		moveVector = Vector3(-background->GetMoveSpeed(), 0, 0);
		motion->SetActive(false);
		pos += moveVector * ELTime;
	}
	gun->SetPos(pos + Vector3(0, 0, -1));
}

void Ride::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Ride::Release()
{
	motion->SetDestroy(true);
}
