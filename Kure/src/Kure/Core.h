#pragma once

//krpch.h is first #include in all cpp files, so
//Core.h will always have access to Log.h for the logging macros

//macros for dll import and dll export
#ifdef KR_PLATFORM_WINDOWS
	#ifdef KR_BUILD_DLL
		#define KURE_API __declspec(dllexport)
		#define IMGUI_API __declspec(dllexport)
	#else
		#define KURE_API __declspec(dllimport)
		#define IMGUI_API __declspec(dllimport)
	#endif
#else
	#error Kure only supports Windows!
#endif

#ifdef KR_DEBUG
	#define KR_ENABLE_ASSERTS
#endif

#ifdef KR_ENABLE_ASSERTS
	#define KR_ASSERT(x, ...) {if(!(x)) {KR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define KR_CORE_ASSERT(x, ...) {if(!(x)) {KR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define KR_ASSERT(x, ...)
	#define KR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define KR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
