#pragma once
#include "Singleton.h"


class ResourceManager :
	public Singleton<ResourceManager>
{
public:
	ResourceManager();
	virtual ~ResourceManager();

private:
	map<string, Texture*> m_Texture;
	map<string, LPD3DXEFFECT> m_Shader;

public:
	Texture* LoadTexture(string path);
	vector<Texture*> LoadTextures(string path, int low, int high);

	LPD3DXEFFECT LoadShader(string path);

	void Release();
};

#define Resources ResourceManager::GetInstance()