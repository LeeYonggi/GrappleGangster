#pragma once
#include "Enemy.h"

class Background;
class Car1 :
	public GameObject
{
public:
	Car1(Background *_background);
	virtual ~Car1();

private:
	Vector3 moveVector;
	GameUI* warringUI = nullptr;
	Background* background = nullptr;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void CarCollision();

};

