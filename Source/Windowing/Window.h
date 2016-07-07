#pragma once

#if SUPPORTS_MULTIPLE_WINDOWING_APIS

#include "PlatformSpecific/Windowing/Virtual/Window.h"
typedef void* WindowHandle;

#elif PLATFORM_WINDOWS

#include "PlatformSpecific/Windowing/Win32/Win32Window.h"
typedef Win32Window Window;
typedef HWND WindowHandle;

#endif
