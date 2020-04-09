#include "Time.h"

#include <iostream>

Time Time::s_Instance;

void Time::UpdateTimeImpl()
{
	time = GetTime() - s_StartTime;

	deltaTime = (float)(time - s_LastFrameTime) / 1000.0f;

	s_LastFrameTime = time;
}

void Time::PrintTimeImpl()
{
	std::cout << "[" << time << "] deltaTime = " << deltaTime << " startTime= " << s_StartTime << std::endl;
}

unsigned long Time::GetTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
		.count();
}