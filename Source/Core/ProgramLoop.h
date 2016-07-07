#pragma once

#include "Graphics/GraphicsContext.h"
#include "Windowing/Window.h"

namespace ProgramLoop
{
	void RunUntilQuit(GraphicsContext* graphicsContext, Window* window);
}