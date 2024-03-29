#pragma once
#include "GameObject.h"

class BackEffect :
	public GameObject
{
public:
	BackEffect() {}
	virtual ~BackEffect() { }

private:
	Texture* subTexture;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

