#pragma once
#include "Singleton.h"


struct Texture
{
	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
};
class RenderManager :
	public Singleton<RenderManager>
{
public:
	RenderManager();
	virtual ~RenderManager();

private:
	vector<TexVertex> vertex;
	LPD3DXSPRITE lpSprite;
	Shader* shader;

private:
	void CreateRectVertex();
	void CreateSprite();

public:
	void Draw();

	void DrawTexture(Texture* texture, Vector3 position, Vector2 scale = {1, 1}, 
		float rotation = 0.0f);

	void DrawSprite(Texture* texture, Vector3 position, Vector2 scale = {1, 1},
		float rotation = 0.0f);

};

#define RENDERMANAGER RenderManager::GetInstance()