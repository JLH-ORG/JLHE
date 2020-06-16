#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace JLHE {

	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define JLHE_CORE_TRACE(...)       ::JLHE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JLHE_CORE_INFO(...)        ::JLHE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JLHE_CORE_WARN(...)        ::JLHE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JLHE_CORE_ERROR(...)       ::JLHE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JLHE_CORE_CRITICAL(...)    ::JLHE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros		   	   	 
#define JLHE_TRACE(...)            ::JLHE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JLHE_INFO(...)             ::JLHE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JLHE_WARN(...)             ::JLHE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JLHE_ERROR(...)            ::JLHE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JLHE_CRITICAL(...)         ::JLHE::Log::GetCoreLogger()->critical(__VA_ARGS__)