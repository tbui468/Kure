#include "krpch.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Kure {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		//set pattern (format)
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("KURE"); //initialization of static member
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("APP"); //initialization of static member
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
