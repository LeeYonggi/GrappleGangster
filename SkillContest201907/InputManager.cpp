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

	for (int i = 0; i < KEY_MAX; i++)
		nowKey[i] = GetAsyncKeyState(i) & 0x8000;

	POINT point;
	
	GetCursorPos(&point);
	ScreenToClient(DXUTGetHWND(), &point);

	mouse.x = point.x;
	mouse.y = point.y;
}

float InputManager::GetHorizontal()
{
	float result = 0.0f;

	result += (IsKeyPress(VK_RIGHT) || IsKeyPress('D'));
	result -= (IsKeyPress(VK_LEFT) || IsKeyPress('A'));

	return result;
}

float InputManager::GetVertical()
{
	float result = 0.0f;

	result += (IsKeyPress(VK_UP) || IsKeyPress('W'));
	result -= (IsKeyPress(VK_DOWN) || IsKeyPress('S'));
	
	return result;
}
