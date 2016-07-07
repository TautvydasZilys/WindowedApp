#pragma once

#ifndef _MSC_VER
#error This works only on MSVC!
#endif

#define NOMINMAX

#include <d3d11_2.h>
#include <Windows.h>
#include <wrl.h>

namespace WRL
{
	using namespace Microsoft::WRL;
}

#define DEBUGBREAK __debugbreak()
