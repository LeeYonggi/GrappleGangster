#include "DXUT.h"

#include <random>

Vector3 ScreenToWorldCamera(Vector2 pos)
{
	Vector3 result = Vector3(0, 0, 0);
	result.x = (SCREEN_X / 1280.0f) * pos.x - SCREEN_X * 0.5f;
	result.y = SCREEN_Y * 0.5f - pos.y * (SCREEN_Y / 720.0f);
	return result;
}

Vector2 WorldCameraToScreen(Vector3 pos)
{
	Vector2 result = Vector2(0, 0);
	result.x = (SCREEN_X * 0.5f) + pos.x;
	result.y = (SCREEN_Y * 0.5f) - pos.y;
	return result;
}

Vector3 GetVec3Distance(const Vector3& p1, const Vector3& p2)
{
	Vector3 result = p2 - p1;
	D3DXVec3Normalize(&result, &result);
	return result;
}

float GetVec2ToDegree(const Vector2& p1, const Vector2& p2)
{
	Vector2 d = p2 - p1;

	D3DXVec2Normalize(&d, &d);

	return D3DXToDegree(atan2f(d.y, d.x));
}

float FixZToY(float y)
{
	float result = y + SCREEN_Y * 0.5f;
	return result;
}

int GetRandomNumberBetween(int n1, int n2)
{
	std::random_device rd;
	std::mt19937_64 mersenne(rd());

	std::uniform_int_distribution<int> between(n1, n2);

	return between(mersenne);
}
