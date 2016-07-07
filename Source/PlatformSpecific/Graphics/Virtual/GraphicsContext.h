#pragma once

#include "BackBuffer.h"
#include "Graphics/ShaderStage.h"
#include "Texture.h"
#include "Utils/NonCopyable.h"

class GraphicsContext :
	public NonCopyable
{
public:
	virtual ~GraphicsContext() = 0 { }

	virtual BackBuffer* CreateBackBuffer(void* windowHandle, uint32_t width, uint32_t height) const = 0;
	virtual void FreeBackBuffer(BackBuffer* backBuffer) const = 0;

	virtual void BindTextures(ShaderStage shaderStage, const Texture* const* textures, uint32_t startingSlot, uint32_t textureCount) const = 0;
	virtual void ClearRenderTarget(const RenderTarget* renderTarget, float r, float g, float b) const = 0;
	virtual void SetRenderTarget(const RenderTarget* renderTarget) const = 0;
};
