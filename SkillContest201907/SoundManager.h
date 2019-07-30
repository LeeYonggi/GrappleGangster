#pragma once
#include "Singleton.h"

class CSoundManager;
class CSound;

class SoundManager :
	public Singleton<SoundManager>
{
public:
	SoundManager();
	virtual ~SoundManager();

public:
	map<string, CSound*> soundMap;
	CSoundManager* manager;

public:
	void AddSound(string str, wstring path);
	void PlayWavSound(string str, bool isLoop);
	void DuplicatePlay(string str);
	void Stop(string str);
	void Release();

};

#define SOUNDMANAGER SoundManager::GetInstance()