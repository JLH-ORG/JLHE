#pragma once

#include <random>

namespace JLHE {

	class Random {
	public:
		static void Init();

		static float Float();	// Gives random float between 0.0f and 1.0f
		static float Float(float lower, float upper);
		
		static int Int(int lower, int upper);
		static bool Bool();
	private:
		static std::mt19937 s_RandomGenerator;
		static std::uniform_int_distribution<std::mt19937::result_type> s_Dist;
	};

#define JLHE_RANDOM_FLOAT(l, u)		JLHE::Random::Float(l, u)
#define JLHE_RANDOM_INT				JLHE::Random::Int()
#define JLHE_RANDOM_BOOL			JLHE::Random::Bool()

}