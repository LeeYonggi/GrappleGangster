#pragma once
#include "GameObject.h"
class GameUI :
	public GameObject
{
public:
	GameUI() { }
	GameUI(Texture *texture) : GameObject(texture) { }
	GameUI(float time, vector<Texture*> textures);
	virtual ~GameUI() { }

protected:
	Vector2 length = { 1, 1 };

public:
	EventHandler<int> tuchEventHandler;
	EventHandler<int> downEventHandler;

	vector<Texture*> animeTexture;
	Timer *timer = nullptr;
	float maxTime = 0;

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetLength(Vector2 value) { length = value; }
};

