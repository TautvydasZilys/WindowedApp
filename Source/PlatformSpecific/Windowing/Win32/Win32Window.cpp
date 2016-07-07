#include "PrecompiledHeader.h"
#include "Win32Window.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

Win32Window::Win32Window(const GraphicsContext* graphicsContext) :
	m_IsOpen(false),
	m_GraphicsContext(graphicsContext)
{
	CreateWin32Window();
	
	m_BackBuffer = m_GraphicsContext->CreateBackBuffer(m_Hwnd, m_Width, m_Height);
}

Win32Window::~Win32Window()
{
	m_GraphicsContext->FreeBackBuffer(m_BackBuffer);
}

ATOM Win32Window::GetWndClass()
{
	static ATOM wndClassAtom = 0;

	if (wndClassAtom == 0)
	{
		WNDCLASSEXW wndClassDescription;
		ZeroMemory(&wndClassDescription, sizeof(wndClassDescription));

		wndClassDescription.cbSize = sizeof(wndClassDescription);
		wndClassDescription.style = CS_VREDRAW | CS_HREDRAW;
		wndClassDescription.lpfnWndProc = &WindowProc;
		wndClassDescription.hInstance = reinterpret_cast<HINSTANCE>(&__ImageBase);
		wndClassDescription.lpszClassName = L"Win32Window";

		wndClassAtom = RegisterClassExW(&wndClassDescription);
		Assert(wndClassAtom != 0);
	}

	return wndClassAtom;
}

void Win32Window::CreateWin32Window()
{
	const DWORD extendedStyle = WS_EX_APPWINDOW | WS_EX_NOREDIRECTIONBITMAP;
	const DWORD style = WS_POPUPWINDOW | WS_VISIBLE;

	m_Width = 1600;
	m_Height = 900;

	m_Hwnd = CreateWindowExW(extendedStyle, reinterpret_cast<LPCWSTR>(GetWndClass()), L"Win32Window", style, 200, 200, m_Width, m_Height, nullptr, nullptr, reinterpret_cast<HINSTANCE>(&__ImageBase), this);
	Assert(m_Hwnd != nullptr);

	m_IsOpen = true;
}

static inline Win32Window* GetThisFromHwnd(HWND hwnd)
{
	auto _this = reinterpret_cast<Win32Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	Assert(_this != nullptr);
	return _this;
}

LRESULT CALLBACK Win32Window::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			auto createStruct = reinterpret_cast<CREATESTRUCTW*>(lParam);
			SetLastError(ERROR_SUCCESS);
			SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
			Assert(GetLastError() == 0);
		}
		break;

	case WM_DESTROY:
		{
			GetThisFromHwnd(hwnd)->m_IsOpen = false;
		}
		break;
	}

	return DefWindowProcW(hwnd, message, wParam, lParam);
}

void Win32Window::PumpEvents()
{
	MSG message;

	while (PeekMessageW(&message, m_Hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}
}