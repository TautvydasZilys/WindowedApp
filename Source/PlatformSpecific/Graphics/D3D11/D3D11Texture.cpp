#include "PrecompiledHeader.h"
#include "D3D11Texture.h"

D3D11Texture::D3D11Texture(ID3D11Device* device, WRL::ComPtr<ID3D11Texture2D> texture, DXGI_FORMAT format, uint32_t mipLevels, bool isReadable) :
	m_Texture(std::move(texture))
{
	if (isReadable)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDescription;
		srvDescription.Format = format;
		srvDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDescription.Texture2D.MipLevels = mipLevels;
		srvDescription.Texture2D.MostDetailedMip = 0;

		auto hr = device->CreateShaderResourceView(texture.Get(), &srvDescription, &m_ShaderResourceView);
		Assert(SUCCEEDED(hr));
	}
}
