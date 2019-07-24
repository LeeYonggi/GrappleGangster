#pragma once
#include "GameObject.h"
class Gun :
	public GameObject
{
public:
	Gun(Texture *texture) : GameObject(texture) { }
	virtual ~Gun() { }

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

