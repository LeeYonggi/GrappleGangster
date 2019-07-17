#include "DXUT.h"
#include "MainProc.h"

#include "Player.h"

MainProc::MainProc()
{
}


MainProc::~MainProc()
{
}

void MainProc::Init()
{
	player = new Player();
	player->Init();
}

void MainProc::Update()
{

}

void MainProc::Render()
{
	CAMERAMANAGER->SetCamera();
	player->Render();
}

void MainProc::Release()
{
	CAMERAMANAGER->ReleaseInstance();
	RENDERMANAGER->ReleaseInstance();
	Resources.ReleaseInstance();
}
