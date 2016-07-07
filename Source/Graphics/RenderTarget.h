#pragma once

#include "Texture.h"

#if SUPPORTS_MULTIPLE_GFX_APIS

#include "PlatformSpecific/Graphics/Virtual/RenderTarget.h"

#elif SUPPORTS_D3D11

#include "PlatformSpecific/Graphics/D3D11/D3D11RenderTarget.h"
typedef D3D11RenderTarget RenderTarget;

#endif
