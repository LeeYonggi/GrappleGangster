#pragma once

#define Property(in) __declspec(property(in))

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

protected:
	Vector3 pos	  = Vector3(0, 0, 0);
	Vector2 scale = Vector2(1, 1);
	float rotate  = 0;

	Texture *mainTexture;

public:
	virtual void Init()		= 0;
	virtual void Update()	= 0;
	virtual void Render()	= 0;
	virtual void Release()	= 0;

public:
	Property(get = GetPos, put = SetPos) Vector3 Position;
	Property(get = GetScale, put = SetScale) Vector2 scale;
	Property(get = GetRotate, put = SetRotate) float rotate;

public:
	Vector3 GetPos() { return pos; }
	void SetPos(Vector3 value) { pos = value; }

	Vector2 GetScale() { return scale; }
	void SetScale(Vector2 value) { scale = value; }

	float GetRotate() { return rotate; }
	void SetRotate(float value) { rotate = value; }
};
