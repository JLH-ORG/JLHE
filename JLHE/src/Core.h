#pragma once

#ifdef JLHE_DEBUG
	#define JLHE_ENABLE_ASSERTS
#endif

#ifdef JLHE_ENABLE_ASSERTS
	#define JLHE_ASSERT(x, ...) { if(!(x)) {JLHE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JLHE_CORE_ASSERT(x, ...) { if(!(x)) {JLHE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JLHE_ASSERT(x, ...)
	#define JLHE_CORE_ASSERT(x, ...)
#endif