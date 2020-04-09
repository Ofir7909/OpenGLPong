#pragma once

#include <chrono>
#include <memory>

class Time
{
  public:
	static Time& Get() { return s_Instance; };

	inline static void UpdateTime() { Get().UpdateTimeImpl(); }
	inline static void PrintTime() { Get().PrintTimeImpl(); }

  private:
	Time() { s_StartTime = GetTime(); }

	unsigned long GetTime();
	void UpdateTimeImpl();
	void PrintTimeImpl();

  public:
	float deltaTime	   = 0; // time since last frame in seconds
	unsigned long time = 0; // current time since start of the game in ms

  private:
	unsigned long s_StartTime;		   // the time at the start of the game(ms since epoch)
	unsigned long s_LastFrameTime = 0; // last frame time (ms since start of game)
	static Time s_Instance;
};
