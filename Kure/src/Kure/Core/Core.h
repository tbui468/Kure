#pragma once

//krpch.h is first #include in all cpp files, so
//Core.h will always have access to Log.h for the logging macros

//platform detection
#ifdef _WIN32
	#ifdef _WIN64
		#define KR_PLATFORM_WINDOWS
	#else
		#error "x86 builds are not supported"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define KR_PLATFORM_IOS
		#error "IOS is not currently supported!"
	#elif TARGET_OS_MAC == 1
		#define KR_PLATFORM_MACOS
		#error "MACOS is not currently supported"
	#else
		#error "Unknown Apples platforom"
	#endif
//need to check android first bc android is based
//on linux kernel and has __linux__ defined
#elif defined(__ANDROID__)
	#define KR_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define KR_PLATFORM_LINUX
	#error "Linux is not supported"
#else
	#error "Unknown platform"
#endif //end of platform detection

//macros for dll import and dll export
#ifdef KR_PLATFORM_WINDOWS
#ifdef KR_BUILD_DLL
#define KURE_API
#else
#define KURE_API
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



namespace Kure {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
