#include "DXUT.h"
#include "Timer.h"

std::list<Timer*> Timer::timerContainer;
float Timer::timeScale = 1.0f;

void Timer::Update(float elapsedTime, float nowTime)
{
	if (isEnd == true)
		return;

	if (isPause == false)
		anyTime -= elapsedTime * (isInfluence ? timeScale : 1.0f);

	if (anyTime <= 0)
	{
		isEnd = true;
		anyTime = 0;
	}
}

Timer::Timer(float delay)
{
	anyTime = delay;
}

void Timer::Reset(float delay)
{
	isEnd = false;
	isPause = false;

	anyTime = delay;
}

void Timer::Pause(bool flag)
{
	isPause = flag;
}

void Timer::TimerUpdate(float elapsedTime)
{
	for each (auto iter in timerContainer)
	{
		iter->Update(elapsedTime, DXUTGetTime());
	}
}

Timer* Timer::AddTimer(float delay)
{
	Timer* timer = new Timer(delay);
	timerContainer.push_back(timer);
	return timer;
}

void Timer::PauseAll(bool flag)
{
	for each (auto iter in timerContainer)
	{
		iter->Pause(flag);
	}
}

void Timer::RemoveAll()
{
	for(auto iter = timerContainer.begin(); iter != timerContainer.end(); )
	{
		Timer* timer = *iter;
		iter = timerContainer.erase(iter);
		SAFE_DELETE(timer);
	}
}

void Timer::RemoveTimer(Timer* timer)
{
	if (timer == nullptr)
		return;

	timerContainer.remove(timer);
	SAFE_DELETE(timer);
}

void Timer::SetTimeScale(float time)
{
	timeScale = time;
}

void Timer::SetTimeScaleMin(float time)
{
	timeScale = min(time, timeScale);
}

void Timer::SetTimeScaleMax(float time)
{
	timeScale = max(time, timeScale);
}
