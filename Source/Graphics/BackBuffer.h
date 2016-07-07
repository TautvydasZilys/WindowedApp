#pragma once

#include "RenderTarget.h"

#if SUPPORTS_MULTIPLE_GFX_APIS

#include "PlatformSpecific/Graphics/Virtual/BackBuffer.h"

#elif SUPPORTS_D3D11

#include "PlatformSpecific/Graphics/D3D11/D3D11BackBuffer.h"
typedef D3D11BackBuffer BackBuffer;

#endif
