#include "DXUT.h"
#include "RenderManager.h"


RenderManager::RenderManager()
{
	CreateRectVertex();

}


RenderManager::~RenderManager()
{
}

void RenderManager::CreateRectVertex()
{
	float size = 1.0f;

	vertex.push_back(TexVertex(Vector3(size, size, 0), Vector3(0, 0, -1),	Vector2(1.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(size, -size, 0), Vector3(0, 0, -1),  Vector2(1.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, -size, 0), Vector3(0, 0, -1), Vector2(1.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, -size, 0), Vector3(0, 0, -1), Vector2(1.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, size, 0), Vector3(0, 0, -1),  Vector2(1.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(size, size, 0), Vector3(0, 0, -1),   Vector2(1.f, 1.f)));

	DEVICE->CreateVertexBuffer(sizeof(TexVertex) * 6, 0, TexVertex::FVF, D3DPOOL_DEFAULT, &vb, nullptr);
	
	void * verbogi;
	vb->Lock(0, sizeof(TexVertex) * vertex.size(), &verbogi, 0);
	memcpy(verbogi, &vertex[0], sizeof(TexVertex) * 6);
	vb->Unlock();

}

void RenderManager::Draw()
{
	Matrix matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	DEVICE->SetTransform(D3DTS_WORLD, &matT);


	//----------------------------------//
	// 커스텀 버텍스의 옵션을 지정해준다
	//----------------------------------//
	DEVICE->SetFVF(TexVertex::FVF);

	//----------------------------------//
	// 정점 정보가 들어있는 버텍스버퍼를 지정해준다.
	//  (스트림의 Number(0), VertexBuffer, 시작 Byte, 커스텀버텍스 한개의 사이즈)
	//----------------------------------//
	DEVICE->SetStreamSource(0, vb, 0, sizeof(TexVertex));

	//----------------------------------//
	// VertexBuffer에 있는 정점들을 그린다
	// (옵션, 시작 삼각형, 삼각형 갯수(정점의 갯수 / 3))
	//----------------------------------//
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
