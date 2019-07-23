#pragma once
#include "Enemy.h"
class Enemy1 :
	public Enemy
{
public:
	Enemy1(Vector3 _targetPos, Vector3 spawnPos);
	virtual ~Enemy1();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

