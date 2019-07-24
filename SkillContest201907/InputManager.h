#pragma once
#include "Singleton.h"

constexpr int KEY_MAX = 256;

class InputManager :
	public Singleton<InputManager>
{
private:
	bool nowKey[KEY_MAX];
	bool pastKey[KEY_MAX];
	Vector2 mouse;

private:
	vector<Texture*> mouseTexture;

	vector<float> mouseRotate;

public:

public:
	InputManager();
	~InputManager();

public:
	void KeyUpdate();
	void Render();

public:
	bool IsKeyDown(int key)	 { return (nowKey[key] == true && pastKey[key] == false); }
	bool IsKeyPress(int key) { return (nowKey[key] == true && pastKey[key] == true); }
	bool IsKeyUp(int key)	 { return (nowKey[key] == false && pastKey[key] == true); }

	Vector2 GetMousePos() { return mouse; }

public:
	float GetHorizontal();
	float GetVertical();
};

#define	INPUTMANAGER InputManager::GetInstance()