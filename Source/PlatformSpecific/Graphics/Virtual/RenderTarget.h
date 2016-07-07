#pragma once

#include "Utils/NonCopyable.h"

class RenderTarget :
	public NonCopyable
{
public:
	virtual ~RenderTarget() = 0 { }

	virtual const class Texture* AsTexture() const = 0;
};