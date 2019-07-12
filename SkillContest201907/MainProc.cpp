#include "DXUT.h"
#include "MainProc.h"


MainProc::MainProc()
{
}


MainProc::~MainProc()
{
}

void MainProc::Init()
{
	tex = Resources.AddTexture("Character/test.png");
}

void MainProc::Update()
{

}

void MainProc::Render()
{
	CAMERAMANAGER->SetCamera();
	RENDERMANAGER->DrawTexture(tex, {0, 0, 0});
	RENDERMANAGER->DrawSprite(tex, {0, 0, 0});
}

void MainProc::Release()
{
	CAMERAMANAGER->ReleaseInstance();
	RENDERMANAGER->ReleaseInstance();
	Resources.ReleaseInstance();
}
