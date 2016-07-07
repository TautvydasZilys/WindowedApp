#pragma once

#include "Graphics/BackBuffer.h"
#include "Graphics/GraphicsContext.h"
#include "Utils/NonCopyable.h"

#if SUPPORTS_MULTIPLE_WINDOWING_APIS
#include "Windowing/Window.h"
#endif

class Win32Window :
#if SUPPORTS_MULTIPLE_WINDOWING_APIS
	public Window
#else
	public NonCopyable
#endif
{
public:
	Win32Window(const GraphicsContext* graphicsContext);
	~Win32Window();

	const BackBuffer* GetBackBuffer() const { return m_BackBuffer; }
	bool IsOpen() const { return m_IsOpen; }

	void PumpEvents();

private:
	HWND m_Hwnd;
	const GraphicsContext* m_GraphicsContext;
	BackBuffer* m_BackBuffer;
	uint32_t m_Width;
	uint32_t m_Height;
	bool m_IsOpen;

	static ATOM GetWndClass();
	void CreateWin32Window();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};
