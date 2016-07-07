#pragma once

#include <cstdint>
#include <memory>
#include <string>

#ifdef _MSC_VER
	#define PLATFORM_WINDOWS 1
	#define SUPPORTS_D3D11 1
	#include "PrecompiledHeaderWindows.h"
#else
	#error Unknown platform
#endif

#ifndef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS 0
#endif

#ifndef SUPPORTS_D3D11
#define SUPPORTS_D3D11 0
#endif

#ifndef DEBUGBREAK
#define DEBUGBREAK
#endif

#ifndef SUPPORTS_MULTIPLE_WINDOWING_APIS
#define SUPPORTS_MULTIPLE_WINDOWING_APIS 0
#endif

#ifndef SUPPORTS_MULTIPLE_GFX_APIS
#define SUPPORTS_MULTIPLE_GFX_APIS 1
#endif

#define Assert(x) do { if (!(x)) DEBUGBREAK; } while (false, false)
#define AssertFail() Assert((false, false))