#pragma once
class MainProc
{
public:
	MainProc();
	virtual ~MainProc();

private:
	Texture *tex;

public:
	void Init();
	void Update();
	void Render();
	void Release();
};

