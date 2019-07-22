#pragma once

#define Property(in) __declspec(property(in))

class ObjectManager;
class GameObject
{
	friend ObjectManager;
public:
	GameObject();
	GameObject(Texture* tex) : mainTexture(tex) {}
	virtual ~GameObject();

public:
	enum GAMEOBJECT_STATE : int
	{
		DEFAULT,
		BACKGROUND,
		RIDE,
		PLAYER,
		ENEMY,
		ENEMY_BULLET,
		PLAYER_BULLET,
		EFFECT,
		UI
	};


protected:
	Vector3 pos = Vector3(0, 0, 0);
	Vector2 scale = Vector2(1, 1);
	float rotate = 0;
	Color color = Color(1, 1, 1, 1);

	Texture* mainTexture;

	GAMEOBJECT_STATE tag = DEFAULT;

	bool isActive = true;
	bool isDestroy = false;

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

public:
	Property(get = GetPos, put = SetPos) Vector3 Position;
	Property(get = GetScale, put = SetScale) Vector2 Scale;
	Property(get = GetRotate, put = SetRotate) float Rotate;
	Property(get = GetTag) GAMEOBJECT_STATE Tag;
	Property(get = GetActive, put = SetActive) bool Active;
	Property(get = GetDestroy, put = SetDestroy) bool Destroy;

public:
	Vector3 GetPos() { return pos; }
	void SetPos(Vector3 value) { pos = value; }

	Vector2 GetScale() { return scale; }
	void SetScale(Vector2 value) { scale = value; }

	float GetRotate() { return rotate; }
	void SetRotate(float value) { rotate = value; }

	Color GetColor() { return color; }
	void SetColor(Color value) { color = value; }

	Texture* GetTexture() { return mainTexture; }

	GAMEOBJECT_STATE GetTag() { return tag; }

	bool GetActive() { return isActive; }
	void SetActive(bool value) { isActive = value; }

	bool GetDestroy() { return isDestroy; }
	void SetDestroy(bool value) { isDestroy = value; }
};
