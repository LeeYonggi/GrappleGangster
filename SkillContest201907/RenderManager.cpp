#include "DXUT.h"
#include "RenderManager.h"


RenderManager::RenderManager()
{
	float size = 1.0f;

	vertex.push_back(TexVertex(Vector3(size, size, 0), Vector3(0, 0, -1), Vector2(1.f, 0.f)));
	vertex.push_back(TexVertex(Vector3(size, -size, 0), Vector3(0, 0, -1), Vector2(1.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, -size, 0), Vector3(0, 0, -1), Vector2(0.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, size, 0), Vector3(0, 0, -1), Vector2(0.f, 0.f)));

	plane = CreatePlane();

	vertex.push_back(TexVertex(Vector3(size, size, 0), Vector3(0, 0, -1), Vector2(1.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(size, -size, 0), Vector3(0, 0, -1), Vector2(1.f, 0.f)));
	vertex.push_back(TexVertex(Vector3(-size, -size, 0), Vector3(0, 0, -1), Vector2(0.f, 0.f)));
	vertex.push_back(TexVertex(Vector3(-size, size, 0), Vector3(0, 0, -1), Vector2(0.f, 1.f)));

	flipPlane = CreatePlane();

	CreateSprite();
	shader = Resources->LoadShader("Shader/DefaultShader.fx");
	multiflyShader = Resources->LoadShader("Shader/CircleShader.fx");
}


RenderManager::~RenderManager()
{
	SAFE_RELEASE(plane);
	SAFE_RELEASE(flipPlane);
	SAFE_RELEASE(lpSprite);
}

LPD3DXMESH RenderManager::CreatePlane()
{
	LPD3DXMESH temp = nullptr;

	index.reserve(6);

	index.push_back(0);
	index.push_back(1);
	index.push_back(2);
	index.push_back(2);
	index.push_back(3);
	index.push_back(0);

	D3DXCreateMeshFVF(
		index.size() / 3, 
		vertex.size(), 
		D3DXMESH_MANAGED | D3DXMESH_32BIT, 
		TexVertex::FVF, 
		DEVICE, 
		&temp);

	TexVertex *v = nullptr;

	temp->LockVertexBuffer(0, (void**)&v);

	memcpy(v, &vertex[0], sizeof(TexVertex) * vertex.size());

	temp->UnlockVertexBuffer();

	vertex.clear();

	DWORD* indices = nullptr;

	temp->LockIndexBuffer(0, (void**)&indices);

	memcpy(indices, &index[0], sizeof(DWORD) * index.size());

	temp->UnlockIndexBuffer();

	index.clear();

	DWORD *attribute = nullptr;

	vector<DWORD> attr;
	attr.push_back(0);

	temp->LockAttributeBuffer(0, &attribute);

	memcpy(attribute, &attr[0], sizeof(DWORD) * attr.size());
	
	temp->UnlockAttributeBuffer();

	attr.clear();

	return temp;
}

void RenderManager::CreateSprite()
{
	D3DXCreateSprite(DEVICE, &lpSprite);
}


void RenderManager::DrawSprite(Texture* texture, Vector3 position, Vector2 scale, 
	Vector2 length, float rotation, Color color)
{
	Matrix matW, matT, matR, matS;

	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotation));
	D3DXMatrixTranslation(&matT, position.x, position.y, 0);

	matW = matS * matR * matT;

	lpSprite->SetTransform(&matW);

	Vector3 center = { texture->info.Width * 0.5f, texture->info.Height * 0.5f, 0 };

	RECT re = 
	{	
		0, 0,
		UINT(texture->info.Width * length.x),
		UINT(texture->info.Height * length.y)
	};

	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	lpSprite->Draw(texture->tex, &re, &center, nullptr, color);

	lpSprite->End();
}

void RenderManager::DrawTexture(Texture* texture, Vector3 position, Vector2 scale, float rotation, Color color, bool flip)
{
	Matrix matW, matT, matR, matS;

	D3DXMatrixTranslation(&matT, position.x, position.y, position.z);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotation));
	D3DXMatrixScaling(&matS, scale.x * texture->info.Width * 0.5f,
		scale.y * texture->info.Height * 0.5f, 1);

	matW = matS * matR * matT;

	Matrix viewMat, projMat;
	viewMat = CAMERAMANAGER->GetView();
	projMat = CAMERAMANAGER->GetProjection();

	shader->SetMatrix(D3DXHANDLE("gWorldMat"), &matW);
	shader->SetMatrix(D3DXHANDLE("gViewMat"), &viewMat);
	shader->SetMatrix(D3DXHANDLE("gProjMat"), &projMat);
	shader->SetVector(D3DXHANDLE("gColor"), &D3DXVECTOR4(color.r, color.g, color.b, color.a));

	shader->SetTexture(D3DXHANDLE("gDiffuseTex"), texture->tex);

	UINT numPasses = 0;
	shader->Begin(&numPasses, NULL);
	
	shader->BeginPass(0);
	if (flip)
		flipPlane->DrawSubset(0);
	else
		plane->DrawSubset(0);
	shader->EndPass();
	
	shader->End();
}

void RenderManager::DrawCircleTexture(Texture* mainTexture, float distance,
	Vector3 position, Vector2 scale, float rotation, Color color)
{
	Matrix matW, matT, matR, matS;

	D3DXMatrixTranslation(&matT, position.x, position.y, position.z);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotation));
	D3DXMatrixScaling(&matS, scale.x * mainTexture->info.Width * 0.5f,
		scale.y * mainTexture->info.Height * 0.5f, 1);

	matW = matS * matR * matT;


	Matrix viewMat, projMat;
	viewMat = CAMERAMANAGER->GetView();
	projMat = CAMERAMANAGER->GetProjection();

	multiflyShader->SetMatrix(D3DXHANDLE("gWorldMat"), &matW);
	multiflyShader->SetMatrix(D3DXHANDLE("gViewMat"), &viewMat);
	multiflyShader->SetMatrix(D3DXHANDLE("gProjMat"), &projMat);
	multiflyShader->SetVector(D3DXHANDLE("gColor"), &D3DXVECTOR4(color.r, color.g, color.b, color.a));
	multiflyShader->SetFloat(D3DXHANDLE("gDistance"), distance);

	multiflyShader->SetTexture(D3DXHANDLE("gDiffuseTex"), mainTexture->tex);

	UINT numPasses = 0;
	multiflyShader->Begin(&numPasses, NULL);

	multiflyShader->BeginPass(0);
	plane->DrawSubset(0);
	multiflyShader->EndPass();

	multiflyShader->End();
}
