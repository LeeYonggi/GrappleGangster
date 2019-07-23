#pragma once
#include "GameObject.h"

class MotionBlur
	: public GameObject
{
public:
	MotionBlur(GameObject *targetObj);
	virtual ~MotionBlur();

private:
	GameObject *obj;
	Timer* timer;
	bool isInfluenceBackground = true;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetInFluenceBackground(bool value) { isInfluenceBackground = value; }

};

