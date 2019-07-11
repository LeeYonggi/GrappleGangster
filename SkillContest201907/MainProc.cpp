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
}

void MainProc::Update()
{

}

void MainProc::Render()
{
	CAMERAMANAGER->SetCamera();
	RENDERMANAGER->Draw();
}

void MainProc::Release()
{
	CAMERAMANAGER->ReleaseInstance();
	RENDERMANAGER->ReleaseInstance();
}
