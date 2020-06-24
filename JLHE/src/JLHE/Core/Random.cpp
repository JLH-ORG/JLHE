#include "jlhepch.h"
#include "JLHE/Core/Random.h"

namespace JLHE {

	std::mt19937 Random::s_RandomGenerator;
	std::uniform_int_distribution<std::mt19937::result_type> Random::s_Dist;

	void Random::Init() {
		s_RandomGenerator.seed(std::random_device()());
	}

	float Random::Float() {
		return (float)Random::s_Dist(s_RandomGenerator) / (float)(std::numeric_limits<uint32_t>::max)();
	}

	float Random::Float(float lower, float upper) {
		return lower + Random::Float() * (upper - lower);
	}

	int Random::Int(int lower, int upper) {
		return std::lround(Random::Float(lower, upper));
	}

	bool Random::Bool() {
		return std::lround(Random::Float());
	}

}