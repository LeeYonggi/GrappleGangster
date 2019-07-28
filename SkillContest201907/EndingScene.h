#pragma once
#include "Scene.h"
class EndingScene :
	public Scene
{
private:
	Texture* texture;
	Color color = Color(1, 1, 1, 0);

public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

