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
	map<string, Shader*> m_Shader;

public:
	Texture* LoadTexture(string path);

	Shader* LoadShader(string path);

	void Release();
};

#define Resources (*ResourceManager::GetInstance())