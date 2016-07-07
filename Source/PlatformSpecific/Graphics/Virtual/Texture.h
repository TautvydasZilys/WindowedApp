#pragma once

#include "Utils/NonCopyable.h"

class Texture :
	public NonCopyable
{
public:
	virtual ~Texture() = 0 { }
};
