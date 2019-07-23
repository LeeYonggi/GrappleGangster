#pragma once
#include "GameObject.h"
class Background :
	public GameObject
{
public:
	Background();
	virtual ~Background();

public:
	enum GROUND_COLLISION
	{
		NONE,
		UNACCESS,
		HIT,
	};

private:
	float moveSpeed = 0.0f;

	Vector3 backPosition = Vector3(0, 0, 0);

	Texture* backTexture = nullptr;

	Texture* nowPixelTexture = nullptr;

	vector<Texture*> mainTextures;
	vector<Vector3> texturePosition;

	vector<Texture*> pixelTextures;

public:
	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	float GetMoveSpeed() { return moveSpeed; }
	void PushBackGround();
	void SetPixelTexture(Texture* value) { nowPixelTexture = value; }
	GROUND_COLLISION IsGroundCollision(Vector2 pos);

};

