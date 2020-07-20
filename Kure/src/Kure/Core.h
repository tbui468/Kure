#pragma once

#ifdef KR_PLATFORM_WINDOWS
	#ifdef KR_BUILD_DLL
		#define KURE_API __declspec(dllexport)
	#else
		#define KURE_API __declspec(dllimport)
	#endif
#else
	#error Kure only supports Windows!
#endif
