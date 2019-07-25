#include "DXUT.h"
#include "Gun.h"

void Gun::Init()
{

}

void Gun::Update()
{

}

void Gun::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color, isFlip);
}

void Gun::Release()
{
	Timer::RemoveTimer(timer);
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
