#pragma once

class Player;
class MainProc
{
public:
	MainProc();
	virtual ~MainProc();

public:
	void Init();
	void Update();
	void Render();
	void Release();
};

