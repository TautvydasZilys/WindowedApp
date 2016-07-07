#pragma once

#if SUPPORTS_MULTIPLE_GFX_APIS
#include "PlatformSpecific/Graphics/Virtual/GraphicsContext.h"
#endif

#include "D3D11BackBuffer.h"
#include "Graphics/BackBuffer.h"
#include "Utils/NonCopyable.h"

class D3D11Context :
#if SUPPORTS_MULTIPLE_GFX_APIS
	public GraphicsContext
#else
	public NonCopyable
#endif
{
public:
	D3D11Context();
	~D3D11Context();

	D3D11BackBuffer* CreateBackBuffer(void* windowHandle, uint32_t width, uint32_t height) const;
	void FreeBackBuffer(BackBuffer* backBuffer) const { delete backBuffer; }

	void BindTextures(ShaderStage shaderStage, const Texture* const* textures, uint32_t startingSlot, uint32_t textureCount) const;
	void ClearRenderTarget(const RenderTarget* renderTarget, float r, float g, float b) const;
	void SetRenderTarget(const RenderTarget* renderTarget) const;

private:
	WRL::ComPtr<IDXGIFactory2> m_DxgiFactory;
	WRL::ComPtr<ID3D11Device> m_Device;
	WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	bool m_SupportsTearing;

	void CreateDevice();
};
