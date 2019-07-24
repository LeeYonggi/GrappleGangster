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
	vector<DWORD> index;
	LPD3DXSPRITE lpSprite;
	LPD3DXEFFECT shader;
	LPD3DXEFFECT multiflyShader;
	LPD3DXMESH plane;

private:
	void CreatePlane();
	void CreateSprite();

public:
	void DrawSprite(Texture* texture, Vector3 position, Vector2 scale = {1, 1},
		float rotation = 0.0f, Color color = Color(1, 1, 1, 1));

	void DrawTexture(Texture* texture, Vector3 position, Vector2 scale = {1, 1}, 
		float rotation = 0.0f, Color color = Color(1, 1, 1, 1));

	void DrawCircleTexture(Texture* mainTexture, float distance, Vector3 position, 
		Vector2 scale = {1, 1}, float rotation = 0.0f, Color color = Color(1, 1, 1, 1));
};

#define RENDERMANAGER RenderManager::GetInstance()