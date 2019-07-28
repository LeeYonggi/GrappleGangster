#include "DXUT.h"
#include "Gun.h"

#include "AnimeEffect.h"
#include "Bullet.h"
#include "Cartridge.h"

#include "ChargeUI.h"

void Gun::Init()
{
	gage = new ChargeUI(
		Resources->LoadTexture("UI/ReloadGage/OutLine.png"), 
		Resources->LoadTexture("UI/ReloadGage/Gage.png"),
		Vector2(0, 0),
		&chargeCount);

	OBJECTMANAGER->AddGameObject(gage, GameObject::UI);

	gage->SetActive(false);
}

void Gun::Update()
{
	if (reloadTimer->IsEnd)
	{
		bulletCount = reloadCount;
		reloadTimer->Reset(maxReloadTime);
		reloadTimer->Pause(true);
		gage->SetActive(false);
	}
	Vector2 gagePos = WorldCameraToScreen(owner->GetPos());
	gage->SetPos(Vector3(gagePos.x, gagePos.y - 35, 0));
	gage->SetLength(Vector2(reloadTimer->GetAnyTime() / maxReloadTime, 1));
}

void Gun::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color, isFlip);
}

void Gun::Release()
{
	Timer::RemoveTimer(timer);
	Timer::RemoveTimer(reloadTimer);
	gage->SetDestroy(true);
	gage = nullptr;
}

void Gun::OnDisable()
{
	gage->SetActive(false);
}

void Gun::GunControll(Vector3 pos, Vector2 target)
{
	Vector2 dis = GetVec3Distance(Vector3(pos.x, pos.y, 0), Vector3(target.x, target.y, 0));

	float radian = D3DXToRadian(GetVec2ToDegree(Vector2(0, 0), dis));
	this->SetPos(pos + Vector3(cos(radian) * 20, sin(radian) * 20, 0));
	this->SetRotate(D3DXToDegree(radian));

	if (radian + D3DXToRadian(180) > D3DXToRadian(270) || radian + D3DXToRadian(180) < D3DXToRadian(90))
		this->SetFlip(true);
	else
		this->SetFlip(false);
}

void Gun::GunShoot(GAMEOBJECT_STATE state, float speed)
{
	if (bulletCount < 1)
		return;

	vector<Texture*> anime = Resources->LoadTextures("Effect/gun_effect/%d.png", 1, 5);

	AnimeEffect* effect = new AnimeEffect(0.3f, anime);

	OBJECTMANAGER->AddGameObject(effect, GameObject::EFFECT);

	Vector3 dis, normalVector;

	normalVector = Vector3(cos(D3DXToRadian(rotate)), sin(D3DXToRadian(rotate)), 0);
	dis = normalVector * mainTexture->info.Width * 0.5f;

	effect->SetRotate(rotate);
	effect->SetPos(pos + dis);

	MakeRifleBullet(pos + dis, pos + dis + normalVector, state, true, speed);

	bulletCount -= 1;
}

void Gun::GunShoot(GAMEOBJECT_STATE state, Vector3 target, float speed)
{
	if (bulletCount < 1)
		return;

	vector<Texture*> anime = Resources->LoadTextures("Effect/gun_effect/%d.png", 1, 5);

	AnimeEffect* effect = new AnimeEffect(0.3f, anime);

	OBJECTMANAGER->AddGameObject(effect, GameObject::EFFECT);

	Vector3 dis, normalVector;

	normalVector = GetVec3Distance(pos, target);
	dis = normalVector * mainTexture->info.Width * 0.5f;

	effect->SetRotate(rotate);
	effect->SetPos(pos + dis);

	MakeRifleBullet(pos + dis, target, state, false, speed);

	bulletCount -= 1;
}

void Gun::MakeRifleBullet(Vector3 pos, Vector3 target, GAMEOBJECT_STATE state, bool isInfluenceBackground, float speed)
{
	Vector3 dis = GetVec3Distance(pos, target);

	Bullet* bullet = new Bullet(Resources->LoadTexture("Bullet/Player_Bullet.png"),
		dis * speed);

	bullet->SetPos(pos);

	bullet->SetInFluenceBackground(isInfluenceBackground);
	if (!isInfluenceBackground)
		bullet->SetTargetZ(target);

	OBJECTMANAGER->AddGameObject(bullet, state);

	Background* background = (Background*)(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());

	Cartridge* cartridge = new Cartridge(pos, background);

	OBJECTMANAGER->AddGameObject(cartridge, GameObject::EFFECT);
}

void Gun::Reload()
{
	reloadTimer->Pause(false);
	if(gage)
		gage->SetActive(true);
}

