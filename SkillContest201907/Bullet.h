#pragma once
#include "GameObject.h"

class Bullet
	: public GameObject
{
private:
	Timer* timer;
	Vector3 moveVector;

public:
	Bullet(Texture* tex, Vector3 dir) : GameObject(tex), moveVector(dir) {}

	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

