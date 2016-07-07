#pragma once

#if SUPPORTS_MULTIPLE_GFX_APIS

#include "PlatformSpecific/Graphics/Virtual/GraphicsContext.h"

#elif SUPPORTS_D3D11

#include "PlatformSpecific/Graphics/D3D11/D3D11Context.h"
typedef D3D11Context GraphicsContext;

#else

#error Unknown graphics API

#endif
