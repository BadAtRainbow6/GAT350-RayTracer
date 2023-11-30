#pragma once
#include <stdlib.h>
#include <cstdlib>
#include <utility>

class Random {
public:
	inline void seedRandom(unsigned int seed)
	{
		srand(seed);
	}

	inline float random01()
	{
		return static_cast<float>(std::rand()) / RAND_MAX;
	}

	inline float random(float min, float max)
	{
		if (min > max) {
			std::swap(min, max);
		}

		return min + (max - min) * random01();
	}
};