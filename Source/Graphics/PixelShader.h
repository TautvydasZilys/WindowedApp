#pragma once

#if SUPPORTS_MULTIPLE_GFX_APIS

typedef void PixelShader;

#elif SUPPORTS_D3D11

typedef ID3D11PixelShader PixelShader;

#else

#error Unknown graphics API

#endif