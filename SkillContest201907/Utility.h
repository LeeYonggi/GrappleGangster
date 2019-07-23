#pragma once


template<typename _Ty>
_Ty Lerp(_Ty start, _Ty end, float d)
{
	return start + (end - start) * d;
}

Vector3 ScreenToWorldCamera(Vector2 pos);

Vector3 GetVec3Distance(const Vector3& p1, const Vector3& p2);

float GetVec2ToDegree(const Vector2& p1, const Vector2& p2);

float FixZToY(float y);

int GetRandomNumberBetween(int n1, int n2);