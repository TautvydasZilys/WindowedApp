#pragma once

#if SUPPORTS_MULTIPLE_GFX_APIS
#include "PlatformSpecific/Graphics/Virtual/BackBuffer.h"
#endif

#include "D3D11RenderTarget.h"
#include "Graphics/RenderTarget.h"

class D3D11BackBuffer :
#if SUPPORTS_MULTIPLE_GFX_APIS
	public BackBuffer,
#endif
	public D3D11RenderTarget
{
public:
	D3D11BackBuffer(ID3D11Device* device, WRL::ComPtr<IDXGISwapChain2> swapChain, DXGI_FORMAT format, bool supportsTearing);
	~D3D11BackBuffer();

	const D3D11RenderTarget* AsRenderTarget() const { return this; }

	void Resize() const;
	void Present() const;

private:
	WRL::ComPtr<IDXGISwapChain2> m_SwapChain;
	uint32_t m_PresentFlags;
};
