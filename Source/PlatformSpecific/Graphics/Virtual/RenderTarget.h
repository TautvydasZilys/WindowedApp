#pragma once

class Texture;

class RenderTarget
{
public:
	virtual ~RenderTarget() = 0 { }

	virtual const Texture* AsTexture() const = 0;
};