#include "DXUT.h"
#include "InputManager.h"

InputManager::InputManager()
{
	memset(nowKey, false, sizeof(nowKey));
	memset(pastKey, false, sizeof(pastKey));
}

InputManager::~InputManager()
{
}

void InputManager::KeyUpdate()
{
	memcpy(pastKey, nowKey, sizeof(nowKey));
	memset(nowKey, false, sizeof(nowKey));

	for (int i = 0; i < KEY_MAX; i++)
		nowKey[i] = GetAsyncKeyState(i) & 0x8000;


}
