#pragma once

#if SUPPORTS_MULTIPLE_WINDOWING_APIS

#include "Graphics/BackBuffer.h"
#include "Utils/NonCopyable.h"

class Window :
	public NonCopyable
{
public:
	virtual const BackBuffer* GetBackBuffer() const = 0;
	virtual bool IsOpen() const = 0;

	virtual void PumpEvents() = 0;
};

typedef void* WindowHandle;

#elif PLATFORM_WINDOWS

#include "PlatformSpecific/Windowing/Win32/Win32Window.h"
typedef Win32Window Window;
typedef HWND WindowHandle;

#endif