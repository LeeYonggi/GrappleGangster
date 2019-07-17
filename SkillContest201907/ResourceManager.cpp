#include "DXUT.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	Release();
}

Texture* ResourceManager::LoadTexture(string path)
{
	auto iter = m_Texture.find(path);
	if (iter != m_Texture.end()) return iter->second;

	Texture* temp = new Texture();

	string str = "./Resources/" + path;

	D3DXCreateTextureFromFileExA(
		DEVICE,
		str.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0, 
		&temp->info,
		nullptr,
		&temp->tex);

	m_Texture.insert(make_pair(path, temp));

	return temp;
}

Shader* ResourceManager::LoadShader(string path)
{
	auto iter = m_Shader.find(path);
	if (iter != m_Shader.end()) return iter->second;

	Shader *shader = nullptr;
	LPD3DXBUFFER pError = nullptr;
	string str = "./Resource/" + path;

	DWORD shaderFlags = 0;

	D3DXCreateEffectFromFileA(
		DEVICE,
		str.c_str(),
		NULL, NULL,
		shaderFlags,
		NULL,
		&shader,
		&pError);

	return shader;
}

void ResourceManager::Release()
{
	for (auto iter : m_Texture)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	m_Texture.clear();
}
