#include "DXUT.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	Release();
}

Texture* ResourceManager::AddTexture(string path)
{
	auto iter = m_Texture.find(path);
	if (iter != m_Texture.end()) return nullptr;

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

void ResourceManager::Release()
{
	for (auto iter : m_Texture)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	m_Texture.clear();
}
