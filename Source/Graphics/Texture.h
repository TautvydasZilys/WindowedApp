#pragma once

#if SUPPORTS_MULTIPLE_GFX_APIS

#include "PlatformSpecific/Graphics/Virtual/Texture.h"

#elif SUPPORTS_D3D11

#include "PlatformSpecific/Graphics/D3D11/D3D11Texture.h"
typedef D3D11Texture Texture;

#else

#error Unknown graphics API

#endif
