#pragma once
#include "GameObject.h"
class Gun :
	public GameObject
{
public:
	Gun(Texture *texture) : GameObject(texture) { }
	virtual ~Gun() { }

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

