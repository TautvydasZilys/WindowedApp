#pragma once

class RenderTarget;

class BackBuffer
{
public:
	virtual ~BackBuffer() = 0 { }

	virtual const RenderTarget* AsRenderTarget() const = 0;
	virtual void Resize() const = 0;
	virtual void Present() const = 0;
};
