#pragma once

inline void Log(const char* message)
{
	OutputDebugStringA(message);
}

inline void Log(const wchar_t* message)
{
	OutputDebugStringW(message);
}

namespace Logging
{
	extern const char* EndLine;
}