#include "DXUT.h"
#include "Gun.h"

#include "AnimeEffect.h"
#include "Bullet.h"
#include "Cartridge.h"

void Gun::Init()
{
	gage = new GameUI(Resources->LoadTexture("UI/ReloadGage/OutLine.png"));
	gage2 = new GameUI(Resources->LoadTexture("UI/ReloadGage/Gage.png"));

	OBJECTMANAGER->AddGameObject(gage, GameObject::UI);
	OBJECTMANAGER->AddGameObject(gage2, GameObject::UI);

	gage->SetActive(false);
	gage2->SetActive(false);
}

void Gun::Update()
{
	if (bulletCount == 0 && reloadTimer->IsEnd)
	{
		bulletCount = reloadCount;
		reloadTimer->Reset(maxReloadTime);
		reloadTimer->Pause(true);
		gage->SetActive(false);
		gage2->SetActive(false);
	}
	Vector2 gagePos = WorldCameraToScreen(owner->GetPos());
	gage->SetPos(Vector3(gagePos.x, gagePos.y - 35, 0));
	gage2->SetPos(Vector3(gagePos.x, gagePos.y - 35, 1));
	gage2->SetLength(Vector2(reloadTimer->GetAnyTime() / maxReloadTime, 1));
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
	gage2->SetDestroy(true);
}

void Gun::OnDisable()
{
	gage->SetActive(false);
	gage2->SetActive(false);
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

void Gun::GunShoot(Vector3 dis)
{
	vector<Texture*> anime = Resources->LoadTextures("Effect/gun_effect/%d.png", 1, 5);

	AnimeEffect* effect = new AnimeEffect(0.3f, anime);

	OBJECTMANAGER->AddGameObject(effect, GameObject::EFFECT);

	dis = Vector3(cos(D3DXToRadian(rotate)), sin(D3DXToRadian(rotate)), 0);

	effect->SetRotate(rotate);
	effect->SetPos(pos + dis * 10);
}

void Gun::MakeRifleBullet(Vector3 pos, GAMEOBJECT_STATE state, bool isInfluenceBackground, float speed)
{
	if (bulletCount < 1)
		return;

	Vector3 dis = Vector3(cos(D3DXToRadian(rotate)), sin(D3DXToRadian(rotate)), 0);

	Bullet* bullet = new Bullet(Resources->LoadTexture("Bullet/Player_Bullet.png"),
		dis * speed);

	bullet->SetPos(pos);

	bullet->SetInFluenceBackground(isInfluenceBackground);

	OBJECTMANAGER->AddGameObject(bullet, state);

	Background* background = (Background*)(*OBJECTMANAGER->FindGameObjectsWithTag(
		GameObject::BACKGROUND).begin());

	Cartridge* cartridge = new Cartridge(pos, background);

	OBJECTMANAGER->AddGameObject(cartridge, GameObject::EFFECT);

	GunShoot(dis);

	bulletCount -= 1;
}

void Gun::Reload()
{
	reloadTimer->Pause(false);
	gage->SetActive(true);
	gage2->SetActive(true);
}
