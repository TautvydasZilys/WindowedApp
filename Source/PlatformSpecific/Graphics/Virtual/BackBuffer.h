#pragma once

#include "Utils/NonCopyable.h"

class BackBuffer :
	public NonCopyable
{
public:
	virtual ~BackBuffer() = 0 { }

	virtual const class RenderTarget* AsRenderTarget() const = 0;
	virtual void Resize() const = 0;
	virtual void Present() const = 0;
};
