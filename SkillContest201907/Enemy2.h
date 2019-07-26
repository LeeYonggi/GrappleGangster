#pragma once
#include "Enemy.h"
class Enemy2 :
	public Enemy
{
public:
	Enemy2(Vector3 targetPos, Vector3 spawnPos, Player* player);
	virtual ~Enemy2();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

