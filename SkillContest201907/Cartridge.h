#pragma once
#include "GameObject.h"

class Background;
class Cartridge :
	public GameObject
{
public:
	Cartridge(Vector3 spawnPos, Background* _background);
	virtual ~Cartridge();

private:
	Vector2 moveVector;
	Background* background;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:

};

