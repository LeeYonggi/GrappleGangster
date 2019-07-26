#pragma once
#include "GameObject.h"
class Character :
	public GameObject
{
public:
	Character();
	virtual ~Character();

protected:
	int hp = 1;
	int a;
	int b;
	int c;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init()		= 0;
	virtual void Update()	= 0;
	virtual void Render()	= 0;
	virtual void Release()	= 0;

public:
	virtual bool CharacterDie(Vector3 moveVec3) = 0;

public:
	void SetHp(int value) { hp = value; }
	int GetHp() { return hp; }
};

