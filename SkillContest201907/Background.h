#pragma once
#include "GameObject.h"
class Background :
	public GameObject
{
public:
	Background();
	virtual ~Background();

private:
	float moveSpeed = 0.0f;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:

};

