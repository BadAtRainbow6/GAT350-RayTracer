#pragma once
#include <glm/glm.hpp>

class MathUtils {
	template <typename T>
	inline T lerp(const T& a, const T& b, float t) {
		return a + t * (b - a);
	}
};