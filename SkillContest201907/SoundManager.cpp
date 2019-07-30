#include "DXUT.h"
#include "SoundManager.h"

#include "../Optional/SDKwavefile.h"
#include "../Optional/SDKsound.h"

#pragma comment(lib, "dsound.lib")

SoundManager::SoundManager()
{
	manager = new CSoundManager();
	manager->Initialize(DXUTGetHWND(), 2);
}

SoundManager::~SoundManager()
{
	Release();
}

void SoundManager::AddSound(string str, wstring path)
{
	auto iter = soundMap.find(str);

	if (iter != soundMap.end()) return;

	CSound* sound;
	manager->Create(&sound, (LPWSTR)path.c_str());

	soundMap.insert(make_pair(str, sound));
}

void SoundManager::PlayWavSound(string str, bool isLoop)
{
	auto iter = soundMap.find(str);

	if (iter == soundMap.end()) return;

	iter->second->Play(0, isLoop);
}

void SoundManager::DuplicatePlay(string str)
{
	auto iter = soundMap.find(str);

	if (iter == soundMap.end()) return;

	LPDIRECTSOUNDBUFFER buff;
	manager->GetDirectSound()->DuplicateSoundBuffer(iter->second->GetBuffer(0), &buff);

	buff->SetCurrentPosition(0);
	buff->Play(0, 0, 0);
}

void SoundManager::Stop(string str)
{
	auto iter = soundMap.find(str);

	if (iter == soundMap.end()) return;

	iter->second->Stop();
}

void SoundManager::Release()
{
	for (auto iter : soundMap)
		SAFE_DELETE(iter.second);
	SAFE_DELETE(manager);
}
