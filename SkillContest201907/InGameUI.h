#pragma once
#include "GameUI.h"

class InGameUI :
	public GameUI
{
public:
	InGameUI() { }
	virtual ~InGameUI(){ }

private:
	Texture* mainUI;
	Texture* hpUI;
	Texture* box1;
	Texture* box2;
	Texture* gage;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

