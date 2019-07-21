#include "DXUT.h"
#include "RenderManager.h"


RenderManager::RenderManager()
{
	CreatePlane();
	CreateSprite();
	shader = Resources->LoadShader("Shader/DefaultShader.fx");
}


RenderManager::~RenderManager()
{
	SAFE_RELEASE(plane);
	SAFE_RELEASE(lpSprite);
}

void RenderManager::CreatePlane()
{
	float size = 1.0f;

	vertex.reserve(6);

	vertex.push_back(TexVertex(Vector3(size, size, 0), Vector3(0, 0, -1), Vector2(1.f, 0.f)));
	vertex.push_back(TexVertex(Vector3(size, -size, 0), Vector3(0, 0, -1), Vector2(1.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, -size, 0), Vector3(0, 0, -1), Vector2(0.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, size, 0), Vector3(0, 0, -1), Vector2(0.f, 0.f)));

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
		&plane);

	TexVertex *v = nullptr;

	plane->LockVertexBuffer(0, (void**)&v);

	memcpy(v, &vertex[0], sizeof(TexVertex) * vertex.size());

	plane->UnlockVertexBuffer();

	vertex.clear();

	DWORD* indices = nullptr;

	plane->LockIndexBuffer(0, (void**)&indices);

	memcpy(indices, &index[0], sizeof(DWORD) * index.size());

	plane->UnlockIndexBuffer();

	index.clear();

	DWORD *attribute = nullptr;

	vector<DWORD> attr;
	attr.push_back(0);

	plane->LockAttributeBuffer(0, &attribute);

	memcpy(attribute, &attr[0], sizeof(DWORD) * attr.size());
	
	plane->UnlockAttributeBuffer();

	attr.clear();
}

void RenderManager::CreateSprite()
{
	D3DXCreateSprite(DEVICE, &lpSprite);
}


void RenderManager::DrawSprite(Texture* texture, Vector3 position, Vector2 scale, float rotation, Color color)
{
	Matrix matW, matT, matR, matS;

	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotation));
	D3DXMatrixTranslation(&matT, position.x, position.y, position.z);

	matW = matS * matR * matT;

	lpSprite->SetTransform(&matW);

	Vector3 center = { texture->info.Width * 0.5f, texture->info.Height * 0.5f, 0 };

	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	lpSprite->Draw(texture->tex, nullptr, &center, nullptr, color);

	lpSprite->End();
}

void RenderManager::DrawTexture(Texture* texture, Vector3 position, Vector2 scale, float rotation, Color color)
{
	Matrix matW, matT, matR, matS;

	D3DXMatrixTranslation(&matT, position.x, position.y, position.z);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotation));
	D3DXMatrixScaling(&matS, scale.x * texture->info.Width * 0.5f,
		scale.y * texture->info.Height * 0.5f, 1);

	matW = matS * matR * matT;

	D3DMATERIAL9 mtl;
	mtl.Ambient = mtl.Diffuse = mtl.Specular = mtl.Emissive = D3DXCOLOR(1, 1, 1, 1);

	D3DXHANDLE worldHandle, viewHandle, projHandle, textureHandle, colorHandle;
	worldHandle = shader->GetParameterByName(0, "gWorldMat");
	viewHandle = shader->GetParameterByName(0, "gViewMat");
	projHandle = shader->GetParameterByName(0, "gProjMat");
	textureHandle = shader->GetParameterByName(0, "gDiffuseTex");
	colorHandle = shader->GetParameterByName(0, "gColor");

	Matrix viewMat, projMat;
	viewMat = CAMERAMANAGER->GetView();
	projMat = CAMERAMANAGER->GetProjection();

	shader->SetMatrix(worldHandle, &matW);
	shader->SetMatrix(viewHandle, &viewMat);
	shader->SetMatrix(projHandle, &projMat);
	shader->SetVector(colorHandle, &D3DXVECTOR4(color.r, color.g, color.b, color.a));

	shader->SetTexture(textureHandle, texture->tex);

	UINT numPasses = 0;
	shader->Begin(&numPasses, NULL);
	
	shader->BeginPass(0);
	plane->DrawSubset(0);
	shader->EndPass();
	
	shader->End();
}
