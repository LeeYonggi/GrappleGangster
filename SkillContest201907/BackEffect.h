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
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

