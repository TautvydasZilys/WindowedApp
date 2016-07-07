#pragma once

#include "Graphics/PixelShader.h"
#include "Graphics/ShaderStage.h"
#include "Graphics/VertexShader.h"
#include "Utils/NonCopyable.h"

class GraphicsContext :
	public NonCopyable
{
public:
	virtual ~GraphicsContext() = 0 { }

	virtual class BackBuffer* CreateBackBuffer(void* windowHandle, uint32_t width, uint32_t height) const = 0;
	virtual void FreeBackBuffer(class BackBuffer* backBuffer) const = 0;

	virtual void* CreateVertexShader(const uint8_t* byteCode, size_t length) const = 0;
	virtual PixelShader* CreatePixelShader(const uint8_t* byteCode, size_t length) const = 0;
	virtual void FreeVertexShader(VertexShader* vertexShader) const = 0;
	virtual void FreePixelShader(PixelShader* pixelShader) const = 0;

	virtual void SetActiveVertexShader(VertexShader* vertexShader) const = 0;
	virtual void SetActivePixelShader(PixelShader* pixelShader) const = 0;

	virtual void BindTextures(ShaderStage shaderStage, const class Texture* const* textures, uint32_t startingSlot, uint32_t textureCount) const = 0;
	virtual void ClearRenderTarget(const class RenderTarget* renderTarget, float r, float g, float b) const = 0;
	virtual void SetRenderTarget(const class RenderTarget* renderTarget) const = 0;
};
