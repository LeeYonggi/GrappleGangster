#pragma once
#include "Scene.h"
class EndingScene :
	public Scene
{
private:
	Texture* texture;
	Color color = Color(1, 1, 1, 0);

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

