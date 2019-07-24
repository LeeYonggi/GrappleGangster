#pragma once
#include "GameObject.h"

enum TARGET_STATE
{
	MOTION_MANAGED,
	MOTION_PLAYER
};

class MotionBlur
	: public GameObject
{
public:
	MotionBlur(GameObject *targetObj, TARGET_STATE state);
	virtual ~MotionBlur();

private:
	GameObject *obj;
	Timer* timer;

	bool isInfluenceBackground = true;

private:
	TARGET_STATE targetState;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetInFluenceBackground(bool value) { isInfluenceBackground = value; }
	void SetTargetState(TARGET_STATE value) { targetState = value; }
};

