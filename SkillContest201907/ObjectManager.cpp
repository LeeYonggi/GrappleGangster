#include "DXUT.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	Init();
}

ObjectManager::~ObjectManager()
{
	Release();
}

void ObjectManager::Init()
{
	for (int i = 0; i < GameObject::GAMEOBJECT_STATE::UI; i++)
		objTagMap.insert(make_pair((GameObject::GAMEOBJECT_STATE)i, list<GameObject*>()));
}

void ObjectManager::Update()
{
	for (auto iter = objTagMap.begin(); iter != objTagMap.end(); iter++)
	{
		for (auto _iter = iter->second.begin(); _iter != iter->second.end();)
		{
			if ((*_iter)->GetDestroy())
			{
				auto a = *_iter;
				objList.remove(a);

				if (a)
				{
					a->Release();
					delete a;
					a = nullptr;
				}

				_iter = iter->second.erase(_iter);
			}
			else
			{
				if ((*_iter)->GetActive())
					(*_iter)->Update();
				_iter++;
			}
		}
	}
}

bool compare(GameObject *obj1, GameObject *obj2)
{
	if (obj1->GetPos().z > obj2->GetPos().z)
		return true;
	if (obj1->GetPos().z == obj2->GetPos().z)
	{
		if (obj1->GetPos().y > obj2->GetPos().y)
			return true;
	}
	return false;
}

void ObjectManager::Render()
{
	objList.sort(compare);
	for (auto iter = objList.begin(); iter != objList.end(); iter++)
	{
		if ((*iter)->GetActive())
			(*iter)->Render();
	}
}

void ObjectManager::Release()
{
	for (auto iter : objTagMap)
	{
		for (auto _iter : iter.second)
		{
			SAFE_RELEASE(_iter);
			SAFE_DELETE(_iter);
		}
		iter.second.clear();
	}
	objTagMap.clear();
}

const list<GameObject*>& ObjectManager::FindGameObjectsWithTag(GameObject::GAMEOBJECT_STATE tag)
{
	auto iter = objTagMap.find(tag);

	return iter->second;
}
