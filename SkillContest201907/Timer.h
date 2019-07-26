#pragma once

class Timer
{
private:
	float anyTime;

	bool isPause = false;
	bool isEnd = false;
	// timeScale 에 영향을 받는가
	bool isInfluence = true;

	void Update(float elapsedTime, float nowTime);
public:
	Timer(float delay);

	~Timer() {
		
	}

	void Reset(float delay);
	void Pause(bool flag);

	bool GetEnd() { return isEnd; }
	bool GetPause() { return isPause; }

	void SetIsInfluenceOfTimeScale(bool value) { isInfluence = value; }
	bool GetIsInfluenceOfTimeScale() { return isInfluence; }

	__declspec(property(get = GetEnd)) bool IsEnd;
	__declspec(property(get = GetPause)) bool IsPause;
	__declspec(property(get = GetIsInfluenceOfTimeScale, put = SetIsInfluenceOfTimeScale)) bool IsInfluence;

	float GetAnyTime() { return anyTime; }
	//STATIC FIELD

private:
	static std::list<Timer*> timerContainer;
	static float timeScale;
public:
	static void TimerUpdate(float elapsedTime);

	static Timer* AddTimer(float delay);

	static void PauseAll(bool flag);

	static void RemoveTimer(Timer* timer);

	static void SetTimeScale(float time);

	static void SetTimeScaleMin(float time);
	static void SetTimeScaleMax(float time);

	static float GetTimeScale() { return timeScale; }
};

