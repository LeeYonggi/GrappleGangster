#include "DXUT.h"

Vector3 ScreenToWorldCamera(Vector2 pos)
{
	Vector3 result = Vector3(0, 0, 0);
	result.x = pos.x - SCREEN_X * 0.5f;
	result.y = SCREEN_Y * 0.5f - pos.y;
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
