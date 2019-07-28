#include "DXUT.h"
#include "Cartridge.h"

#include "Background.h"
#include "AnimeEffect.h"

Cartridge::Cartridge(Vector3 spawnPos, Background *_background)
{
	pos = spawnPos;

	int x = GetRandomNumberBetween(-100, -80);
	int y = GetRandomNumberBetween(400, 600);
	
	moveVector = Vector2(x, y);

	mainTexture = Resources->LoadTexture("Bullet/Cartridge.png");

	background = _background;

	maxY = GetRandomNumberBetween(0, 60);
}

Cartridge::~Cartridge()
{
}

void Cartridge::Init()
{

}

void Cartridge::Update()
{
	if (pos.y > pos.z - SCREEN_Y * 0.5f - maxY || (GAMEMANAGER->stage == STAGE_3 && pos.y > -90))
	{
		pos += Vector3(moveVector.x, moveVector.y, 0) * ELTime;
		moveVector -= Vector2(200, 1700) * ELTime;
		rotate += GetRandomNumberBetween(400, 700) * ELTime;
	}
	else if (pos.x < -640)
	{
		SetDestroy(true);
	}
	else if (GAMEMANAGER->stage != STAGE_1)
	{
		vector<Texture*> anime = Resources->LoadTextures("Effect/splash/%d.png", 1, 9);

		AnimeEffect* effect = new AnimeEffect(0.8f, anime);

		OBJECTMANAGER->AddGameObject(effect, GAMEOBJECT_STATE::EFFECT);

		effect->SetScale(Vector2(1, 1));

		effect->SetPos(pos);

		SetDestroy(true);
	}
	else
	{
		moveVector = Vector2(-background->GetMoveSpeed(), 0);
		pos += Vector3(moveVector) * ELTime;
		pos.z = 400;
	}
}

void Cartridge::Render()
{
	RENDERMANAGER->DrawTexture(mainTexture, pos, scale, rotate, color);
}

void Cartridge::Release()
{
}
