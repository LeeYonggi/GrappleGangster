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

public:
	template<typename T>
	T* Load(const string& path)
	{
		static_assert(false);
	}

	template <>
	Texture* Load<Texture>(const string& path)
	{
		AddTexture(path);
	}

	Texture* AddTexture(string path);

	void Release();
};

#define Resources (*ResourceManager::GetInstance())