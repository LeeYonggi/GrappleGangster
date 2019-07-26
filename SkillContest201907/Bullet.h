#pragma once
#include "GameObject.h"

class MotionBlur;
class Bullet
	: public GameObject
{
private:
	Timer* timer;
	Vector3 moveVector;

	MotionBlur* motion;

	bool isInfluenceBackground = true;

public:
	Bullet(Texture* tex, Vector3 dir) : GameObject(tex), moveVector(dir) {}

	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetInFluenceBackground(bool value) { isInfluenceBackground = value; }
	Vector3 GetMoveVector() { return moveVector; }
};

