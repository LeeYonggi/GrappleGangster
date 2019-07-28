#pragma once
#include "GameUI.h"

class ChargeUI :
	public GameUI
{
public:
	ChargeUI(Texture *_back, Texture *texture, Vector2 _distance, int *chargeCount);
	virtual ~ChargeUI();

public:
	int* charge = nullptr;
	Vector2 distance;
	Texture* back;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;


};

