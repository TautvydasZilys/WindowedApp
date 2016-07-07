#include "PrecompiledHeader.h"
#include "Core/ProgramLoop.h"
#include "PlatformSpecific/Graphics/D3D11/D3D11Context.h"
#include "PlatformSpecific/Windowing/Win32/Win32Window.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	D3D11Context d3d11Context;
	Win32Window window(&d3d11Context);
	ProgramLoop::RunUntilQuit(&d3d11Context, &window);
	return 0;
}
