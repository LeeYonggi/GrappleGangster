#include "DXUT.h"
#include "Car1.h"

#include "Background.h"
#include "Ride.h"

Car1::Car1(Background* _background)
{
	background = _background;
}

Car1::~Car1()
{
}

void Car1::Init()
{
	int y = GetRandomNumberBetween(-300, -50);
	pos = Vector3(SCREEN_X * 1.0f, y, 0);

	mainTexture = Resources->LoadTexture("Character/Obstacle/Car.png");
	warringUI = new GameUI(0.6f, Resources->LoadTextures("UI/danger_effect/%d.png", 1, 5));

	OBJECTMANAGER->AddGameObject(warringUI, GameObject::UI);

	moveVector = Vector3(-800, 0, 0);
}

void Car1::Update()
{
	pos += moveVector * ELTime;

	Background::GROUND_COLLISION collision = background->IsGroundCollision(Vector2(pos));

	if (collision == Background::UNACCESS_UP)
		pos = Vector3(pos.x, pos.y + 10, pos.z);
	else if (collision == Background::UNACCESS_DOWN)
		pos = Vector3(pos.x, pos.y - 10, pos.z);

	if (pos.x < -SCREEN_X * 0.6f)
		SetDestroy(true);

	pos.z = FixZToY(pos.y);

	CarCollision();

	if (!warringUI) return;

	Vector2 ePos = WorldCameraToScreen(pos);
	
	if (ePos.x > 1280)
		warringUI->SetPos(Vector3(1230, ePos.y, 0));
	else
		warringUI->SetDestroy(true);
}

void Car1::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Car1::Release()
{
	if (warringUI)
		warringUI->SetDestroy(true);
}


void Car1::CarCollision()
{
	auto &ride = OBJECTMANAGER->FindGameObjectsWithTag(GameObject::RIDE);

	for (auto iter : ride)
	{
		if (GameObject::IsCircleCollision(iter->GetPos(), pos, iter->GetRadius(), 40))
		{
			static_cast<Ride*>(iter)->SetHp(0);
		}
	}
}
