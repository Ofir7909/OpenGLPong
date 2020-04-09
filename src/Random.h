#pragma once

#include <random>

class Random
{
  public:
	// Returns a float between 0 to 1.
	static float RandFloat();

  private:
	static bool s_Initialized;
};