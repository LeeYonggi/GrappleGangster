#pragma once
#include "Singleton.h"

class RenderManager :
	public Singleton<RenderManager>
{
public:
	RenderManager();
	virtual ~RenderManager();

private:
	vector<TexVertex> vertex;
	LPDIRECT3DVERTEXBUFFER9 vb;

private:
	void CreateRectVertex();
public:
	void Draw();
};

#define RENDERMANAGER RenderManager::GetInstance()