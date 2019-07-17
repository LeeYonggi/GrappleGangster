#pragma once
#include "Singleton.h"

constexpr int KEY_MAX = 256;

class InputManager :
	public Singleton<InputManager>
{
private:
	int nowKey[KEY_MAX];
	int pastKey[KEY_MAX];

public:

public:
	InputManager();
	~InputManager();

public:
	void KeyUpdate();

public:
	bool IsKeyDown(int key)	 { return (nowKey[key] == true && pastKey[key] == false); }
	bool IsKeyPress(int key) { return (nowKey[key] == true && pastKey[key] == true); }
	bool IsKeyUp(int key)	 { return (nowKey[key] == false && pastKey[key] == true); }

};

