#pragma once
#include "GameObject.h"
class Character :
	public GameObject
{
public:
	Character();
	virtual ~Character();

public:
	enum CINEMA_STATE
	{
		IDLE,
		STAGE_END,
		PLAYER_END
	};

protected:
	int hp = 1;
	CINEMA_STATE cinema_state = CINEMA_STATE::IDLE;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init()		= 0;
	virtual void Update()	= 0;
	virtual void Render()	= 0;
	virtual void Release()	= 0;

public:
	virtual void CharacterDie(Vector3 moveVec3) = 0;

public:
	void SetHp(int value) { hp = value; }
	int GetHp() { return hp; }
	void SetCinemaState(CINEMA_STATE state) { cinema_state = state; }
};

