#include "Random.h"

#include <time.h>

bool Random::s_Initialized = false;

float Random::RandFloat()
{
	if (!s_Initialized) {
		srand(time(NULL));
		s_Initialized = true;
	}
	float num = (float)rand() / RAND_MAX;
	return num;
}
