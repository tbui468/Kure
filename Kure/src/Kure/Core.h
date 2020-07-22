#pragma once

//macros for dll import and dll export
#ifdef KR_PLATFORM_WINDOWS
	#ifdef KR_BUILD_DLL
		#define KURE_API __declspec(dllexport)
	#else
		#define KURE_API __declspec(dllimport)
	#endif
#else
	#error Kure only supports Windows!
#endif

//asserts
#ifdef KR_ENABLE_ASSERTS
	#define KR_ASSERT(x, ...) {if(!(x)) {HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define KR_CORE_ASSERT(x, ...) {if(!(x)) {HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define KR_ASSERT(x, ...)
	#define KR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
