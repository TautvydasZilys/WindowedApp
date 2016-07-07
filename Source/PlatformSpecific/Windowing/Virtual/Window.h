#pragma once

#include "Graphics/BackBuffer.h"
#include "Utils/NonCopyable.h"

class Window :
	public NonCopyable
{
public:
	virtual const BackBuffer* GetBackBuffer() const = 0;
	virtual bool IsOpen() const = 0;

	virtual void PumpEvents() = 0;
};
