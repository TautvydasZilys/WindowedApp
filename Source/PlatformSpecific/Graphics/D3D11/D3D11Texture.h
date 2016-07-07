#pragma once

#if SUPPORTS_MULTIPLE_GFX_APIS
#include "PlatformSpecific/Graphics/Virtual/Texture.h"
#endif

#include "Graphics/ShaderStage.h"
#include "Utils/NonCopyable.h"

class D3D11Texture :
#if SUPPORTS_MULTIPLE_GFX_APIS
	public Texture
#else
	public NonCopyable
#endif
{
public:
	D3D11Texture(ID3D11Device* device, WRL::ComPtr<ID3D11Texture2D> texture, DXGI_FORMAT format, uint32_t mipLevels, bool isReadable);

	inline ID3D11Texture2D* GetTexture() const { return m_Texture.Get(); }
	inline ID3D11ShaderResourceView* GetShaderResourceView() const { return m_ShaderResourceView.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
};