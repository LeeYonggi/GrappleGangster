#include "DXUT.h"
#include "GameObject.h"

#include "ObjectManager.h"

GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::Update()
{
}

void GameObject::Render()
{
}

void GameObject::Release()
{
}

void GameObject::OnEnable()
{

}

void GameObject::OnDisable()
{
}

void GameObject::SetActive(bool value)
{
	isActive = value;
	if (value == true)
		OnEnable();
	else
		OnDisable();
}

bool GameObject::IsCircleCollision(Vector3 p1, Vector3 p2, float r1, float r2)
{
	Vector3 temp = p2 - p1;

	float xy = (temp.x * temp.x) + (temp.y * temp.y);
	float d = (temp.z * temp.z) + xy;

	return (sqrt(d) < r1 + r2);
}
