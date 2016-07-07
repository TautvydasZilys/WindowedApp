#pragma once

#if SUPPORTS_MULTIPLE_GFX_APIS
#include "PlatformSpecific/Graphics/Virtual/RenderTarget.h"
#endif

#include "D3D11Texture.h"

class D3D11RenderTarget :
#if SUPPORTS_MULTIPLE_GFX_APIS
	public RenderTarget,
#endif
	public D3D11Texture
{
public:
	D3D11RenderTarget(ID3D11Device* device, WRL::ComPtr<ID3D11Texture2D> colorBuffer, DXGI_FORMAT format);
	~D3D11RenderTarget();

	const D3D11Texture* AsTexture() const { return this; }
	inline ID3D11RenderTargetView* GetRenderTargetView() const { return m_RenderTargetView.Get(); }
	inline ID3D11DepthStencilView* GetDepthStencilView() const { return m_DepthStencilView.Get(); }

private:
	WRL::ComPtr<ID3D11Texture2D> m_DepthBuffer;
	WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
	WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
};

