#include "PrecompiledHeader.h"
#include "ProgramLoop.h"

void ProgramLoop::RunUntilQuit(GraphicsContext* graphicsContext, Window* window)
{
	const auto backBuffer = window->GetBackBuffer();
	const auto backBufferRT = backBuffer->AsRenderTarget();

	while (window->IsOpen())
	{
		window->PumpEvents();

		for (int i = 0; i < 8; i++)
		{
			//backBuffer.Clear((i & 0x4) != 0, (i & 0x2) != 0, (i & 0x1) != 0);
			graphicsContext->ClearRenderTarget(backBufferRT, 1, 0, 0);
			backBuffer->Present();
		}
	}
}