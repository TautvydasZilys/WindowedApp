#include "PrecompiledHeader.h"
#include "D3D11BackBuffer.h"
#include "DXGIMisc.h"

static inline WRL::ComPtr<ID3D11Texture2D> ExtractTextureFromSwapChain(IDXGISwapChain2* swapChain);

D3D11BackBuffer::D3D11BackBuffer(ID3D11Device* device, WRL::ComPtr<IDXGISwapChain2> swapChain, DXGI_FORMAT format, bool supportsTearing) :
	D3D11RenderTarget(device, ExtractTextureFromSwapChain(swapChain.Get()), format),
	m_SwapChain(std::move(swapChain))
{
	m_PresentFlags = supportsTearing ? DXGI_PRESENT_ALLOW_TEARING : 0;
}

D3D11BackBuffer::~D3D11BackBuffer()
{
}

void D3D11BackBuffer::Resize() const
{
	AssertFail();
}

void D3D11BackBuffer::Present() const
{
	Assert(m_SwapChain != nullptr);

	auto hr = m_SwapChain->Present(0, m_PresentFlags);
	Assert(SUCCEEDED(hr));
}

static inline WRL::ComPtr<ID3D11Texture2D> ExtractTextureFromSwapChain(IDXGISwapChain2* swapChain)
{
	WRL::ComPtr<ID3D11Texture2D> texture;
	auto hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &texture);
	Assert(SUCCEEDED(hr));
	return texture;
}
