#pragma once
#include "Singleton.h"

#include "GameObject.h"

class ObjectManager :
	public Singleton<ObjectManager>
{
public:
	ObjectManager();
	virtual ~ObjectManager();

private:
	list<GameObject*> objList;
	map<GameObject::GAMEOBJECT_STATE, list<GameObject*>> objTagMap;

public:
	void Init();
	void Update();
	void Render();
	void Release();

public:
	template<typename T>
	T *AddGameObject(T *obj)
	{
		obj->Init();

		objList.push_back(obj);

		auto iter = objTagMap.find(obj->GetTag());

		iter->second.push_back(obj);

		return obj;
	}

public:
	const list<GameObject*> &FindGameObjectsWithTag(GameObject::GAMEOBJECT_STATE tag);
};

#define OBJECTMANAGER ObjectManager::GetInstance()