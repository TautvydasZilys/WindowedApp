#pragma once

#if SUPPORTS_MULTIPLE_GFX_APIS

typedef void VertexShader;

#elif SUPPORTS_D3D11

typedef ID3D11VertexShader VertexShader;

#else

#error Unknown graphics API

#endif
