#pragma once

class Player;
class MainProc
{
public:
	MainProc();
	virtual ~MainProc();

private:
	Texture *tex;
	Player* player;

public:
	void Init();
	void Update();
	void Render();
	void Release();
};

