#pragma once
#include "GameObject.h"
class AnimeEffect :
	public GameObject
{
public:
	AnimeEffect(float time, vector<Texture*> anime);
	virtual ~AnimeEffect();

private:
	Timer* timer = nullptr;
	vector<Texture*> textures;
	float maxTime = 0.0f;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

