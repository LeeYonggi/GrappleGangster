#include "DXUT.h"
#include "RenderManager.h"


RenderManager::RenderManager()
{
	CreateRectVertex();
	CreateSprite();
	shader = Resources.LoadShader("Shader/DefaultShader.fx");
}


RenderManager::~RenderManager()
{
	SAFE_RELEASE(lpSprite);
}

void RenderManager::CreateRectVertex()
{
	float size = 48.0f;

	vertex.reserve(6);

	vertex.push_back(TexVertex(Vector3(size, size, 0), Vector3(0, 0, -1),	Vector2(1.f, 0.f)));
	vertex.push_back(TexVertex(Vector3(size, -size, 0), Vector3(0, 0, -1),  Vector2(1.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, -size, 0), Vector3(0, 0, -1), Vector2(0.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, -size, 0), Vector3(0, 0, -1), Vector2(0.f, 1.f)));
	vertex.push_back(TexVertex(Vector3(-size, size, 0), Vector3(0, 0, -1),  Vector2(0.f, 0.f)));
	vertex.push_back(TexVertex(Vector3(size, size, 0), Vector3(0, 0, -1),   Vector2(1.f, 0.f)));
}

void RenderManager::CreateSprite()
{
	D3DXCreateSprite(DEVICE, &lpSprite);
}

void RenderManager::Draw()
{
	Matrix matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	DEVICE->SetTransform(D3DTS_WORLD, &matT);
	
	DEVICE->SetFVF(TexVertex::FVF);

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		vertex.size() / 3,
		&vertex[0],
		sizeof(TexVertex));
}

void RenderManager::DrawTexture(Texture* texture, Vector3 position, Vector2 scale, float rotation)
{
	Matrix matW, matT, matR, matS;

	D3DXMatrixTranslation(&matT, position.x, position.y, position.z);
	D3DXMatrixRotationZ(&matR, D3DXToRadian(rotation));
	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);

	matW = matS * matR * matT;

	//DEVICE->SetTransform(D3DTS_WORLD, &matW);

	D3DMATERIAL9 mtl;
	mtl.Ambient = mtl.Diffuse = mtl.Specular = mtl.Emissive = D3DXCOLOR(1, 1, 1, 1);

	//DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//DEVICE->SetFVF(TexVertex::FVF);

	//DEVICE->SetTexture(0, texture->tex);

	//DEVICE->SetMaterial(&mtl);

	D3DXHANDLE handle;
	shader->GetParameterByName(handle, "gWorldMat");
	shader->SetMatrix(handle, &matW);
	shader->GetParameterByName(handle, "gViewMat");
	shader->SetMatrix(handle, &CAMERAMANAGER->GetView());
	shader->GetParameterByName(handle, "gProjMat");
	shader->SetMatrix(handle, &CAMERAMANAGER->GetProjection());


	UINT numPasses = 0;
	shader->Begin(&numPasses, NULL);

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		vertex.size() / 3,
		&vertex[0],
		sizeof(TexVertex));

	shader->End();
}

void RenderManager::DrawSprite(Texture* texture, Vector3 position, Vector2 scale, float rotation)
{
	Matrix matW, matT, matR, matS;

	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);
	D3DXMatrixRotationZ(&matR, rotation);
	D3DXMatrixTranslation(&matT, position.x, position.y, position.z);

	matW = matS * matR * matT;

	lpSprite->SetTransform(&matW);

	Vector3 center = { texture->info.Width * 0.5f, texture->info.Height * 0.5f, 0 };

	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	lpSprite->Draw(texture->tex, nullptr, &center, nullptr, D3DXCOLOR(1, 1, 1, 1));

	lpSprite->End();
}
