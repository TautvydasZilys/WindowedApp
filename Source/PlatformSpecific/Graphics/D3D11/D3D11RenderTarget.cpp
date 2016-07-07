#include "PrecompiledHeader.h"
#include "D3D11RenderTarget.h"

D3D11RenderTarget::D3D11RenderTarget(ID3D11Device* device, WRL::ComPtr<ID3D11Texture2D> colorBuffer, DXGI_FORMAT format) :
	D3D11Texture(device, std::move(colorBuffer), format, 1, false)
{
	D3D11_RENDER_TARGET_VIEW_DESC rtvDescription;
	rtvDescription.Format = format;
	rtvDescription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDescription.Texture2D.MipSlice = 0;

	auto hr = device->CreateRenderTargetView(GetTexture(), &rtvDescription, &m_RenderTargetView);
	Assert(SUCCEEDED(hr));
}

D3D11RenderTarget::~D3D11RenderTarget()
{
}
