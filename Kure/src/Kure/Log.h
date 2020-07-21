#pragma once

#include <memory>

#include "Core.h" //needed for KURE_API
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" //output stream operator for spdlog

namespace Kure {

	class KURE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		
	};

}

//core log macros
#define KR_CORE_TRACE(...)   ::Kure::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KR_CORE_INFO(...)    ::Kure::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KR_CORE_WARN(...)    ::Kure::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KR_CORE_ERROR(...)   ::Kure::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KR_CORE_FATAL(...)   ::Kure::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log macros
#define KR_TRACE(...)   ::Kure::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KR_INFO(...)    ::Kure::Log::GetClientLogger()->info(__VA_ARGS__)
#define KR_WARN(...)    ::Kure::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KR_ERROR(...)   ::Kure::Log::GetClientLogger()->error(__VA_ARGS__)
#define KR_FATAL(...)   ::Kure::Log::GetClientLogger()->fatal(__VA_ARGS__)







