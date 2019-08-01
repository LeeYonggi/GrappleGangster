#include "DXUT.h"
#include "MainScene.h"

#include "GameUI.h"
#include "InGameScene.h"

void MainScene::Init()
{
	timer = Timer::AddTimer(1.0f);
	OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/Background.png")), 
		GameObject::UI)->SetPos(Vector3(630, 360, 4));

	title = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/title.png")),
		GameObject::UI);
	title->SetPos(Vector3(630, 360, 0));
	title->SetActive(false);

	player = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/Player.png")),
		GameObject::UI);
	player->SetPos(Vector3(0, 0, 2));

	enemy = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/Enemy.png")),
		GameObject::UI);
	enemy->SetPos(Vector3(1280, 0, 2));

	fog1 = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/Fog1.png")),
		GameObject::UI);
	fog1->SetPos(Vector3(0, 0, 3));

	fog2 = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/Fog2.png")),
		GameObject::UI);
	fog2->SetPos(Vector3(1280, 0, 3));

	start = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/start.png")),
		GameObject::UI);
	start->SetPos(Vector3(142, 250, 0));
	start->downEventHandler.AddListener(new Event<int>([](Object, int) { SCENEMANAGER->AddScene(new InGameScene, true); }));
	start->SetActive(false);

	howTo = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/how_to.png")),
		GameObject::UI);
	howTo->SetPos(Vector3(142, 416, 0));
	howTo->downEventHandler.AddListener(new Event<int>([&](Object, int) { mainHowTo->SetActive(true); }));
	howTo->SetActive(false);

	rank = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/rank.png")),
		GameObject::UI);
	rank->SetPos(Vector3(142, 586, 0));
	rank->downEventHandler.AddListener(new Event<int>([&](Object, int) { mainRank->SetActive(true); }));
	rank->SetActive(false);

	quit = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/quit.png")),
		GameObject::UI);
	quit->SetPos(Vector3(1108, 609, 0));
	quit->downEventHandler.AddListener(new Event<int>([](Object, int) { PostQuitMessage(WM_DESTROY); }));
	quit->SetActive(false);

	mainRank = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/Ranking.png")),
		GameObject::UI);
	mainRank->SetPos(Vector3(640, 360, -1));
	mainRank->SetActive(false);

	mainHowTo = OBJECTMANAGER->AddGameObject(new GameUI(Resources->LoadTexture("UI/MainScene/Howto.png")),
		GameObject::UI);
	mainHowTo->SetPos(Vector3(640, 360, -1));
	mainHowTo->SetActive(false);
	SOUNDMANAGER->AddSound("MainGame", L"./Resources/Music/Action Game.wav");
	SOUNDMANAGER->PlayWavSound("MainGame", true);
}

void MainScene::Update()
{
	if (!timer->IsEnd)
	{
		player->SetPos(Lerp(player->GetPos(), Vector3(640, 360, 2), 0.1f));
		enemy->SetPos(Lerp(enemy->GetPos(), Vector3(640, 360, 2), 0.1f));
	}
	else
	{
		playerCos += 0.1f;
		player->SetPos(Vector3(640 + cos(playerCos) * 50, 360, 2));

		enemyCos += 0.1f;
		enemy->SetPos(Vector3(640 + sin(enemyCos) * 50, 360, 2));

		start->SetActive(true);
		title->SetActive(true);
		rank->SetActive(true);
		howTo->SetActive(true);
		quit->SetActive(true);
	}

	fog1->SetPos(Lerp(fog1->GetPos(), player->GetPos(), 0.1f));
	fog1->SetPos({ fog1->GetPos().x, fog1->GetPos().y, 3 });

	fog2->SetPos(Lerp(fog2->GetPos(), enemy->GetPos(), 0.1f));
	fog2->SetPos({ fog2->GetPos().x, fog2->GetPos().y, 3 });
}

void MainScene::Render()
{

	if (mainHowTo->GetActive() == true && INPUTMANAGER->IsKeyDown(VK_LBUTTON))
		mainHowTo->SetActive(false);
	if (mainRank->GetActive() == true && INPUTMANAGER->IsKeyDown(VK_LBUTTON))
		mainRank->SetActive(false);
}

void MainScene::Release()
{
	Timer::RemoveTimer(timer);
	SOUNDMANAGER->Stop("MainGame");
}
