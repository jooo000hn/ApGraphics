#include "Window.h"

WindowData::WindowData()
	:SystemData(SystemType::Sys_Window)
	, width(-1), height(-1)
	, bits(-1), windowTitle(std::tstring(""))
	, fullScreen(false)
{

}

WindowData::WindowData(int width, int height, std::tstring& title /*= std::tstring("ApEngine")*/, int b /*= 32*/, bool fullScreen /*= false */)
	:SystemData(SystemType::Sys_Window)
	, width(width), height(height)
	, bits(bits), windowTitle(title)
	, fullScreen(fullScreen)
{

}

ResizeData::ResizeData()
	: mustResize(false)
	, newWidth(-1)
	, newHeight(-1)
{

}

ResizeData::ResizeData(int resize, int newWidth, int newHeight)
	: mustResize(resize)
	, newWidth(newWidth)
	, newHeight(newHeight)
{

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
	{
		CREATESTRUCT *pCS = (CREATESTRUCT*)lParam;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)pCS->lpCreateParams);
	}
	else
	{
		Window* pWindow = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pWindow)
		{
			return pWindow->HandleEvent(hWnd, msg, wParam, lParam);
		}
	}
}

LRESULT Window::HandleEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		if (!HIWORD(wParam))
		{
			this->Activate();
		}
		else
		{
			this->DeActivate();
		}
		break;
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);

		m_ResizeData.mustResize = true;
		m_ResizeData.newWidth = width;
		m_ResizeData.newHeight = height;
	}
		break;
	case WM_DISPLAYCHANGE:
	{
		InvalidateRect(hWnd, NULL, FALSE);
	}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Window(const WindowData& data)
	: System(data)
	, m_hWindow(NULL)
	, m_hDC(NULL)
	, m_hInst(NULL)
	, m_Width(data.width)
	, m_Height(data.height)
	, m_bits(data.bits)
	, m_bFullScreen(data.fullScreen)
	, m_Title(data.windowTitle)
	, m_ResizeData()
{

}

bool Window::Initialize()
{
	System::Initialize();
	unsigned int pixelFormat;

	DWORD dwExStyle;
	DWORD dwStyle;

	RECT wndRect;
	wndRect.left = (long)0;
	wndRect.right = (long)m_Width;
	wndRect.top = (long)0;
	wndRect.bottom = (long)m_Height;

	WNDCLASS wndClass;
	std::tstring className = m_Title;

	wndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = (LPCWSTR)className.c_str();

	if (!RegisterClass(&wndClass))
	{
		// log("failed to register window");
		return false;
	}

	if (m_bFullScreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = m_Width;
		dmScreenSettings.dmPelsHeight = m_Height;
		dmScreenSettings.dmBitsPerPel = m_bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// log(the request fullscreen mode is not supported by your video card);
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;
		}
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&wndRect, dwStyle, FALSE, dwExStyle);

	if (!(m_hWindow = CreateWindow(
		dwExStyle,
		className.c_str(),
		className.c_str(),
		dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 0, 
		wndRect.right - wndRect.left,
		wndRect.bottom - wndRect.top,
		NULL,
		NULL,
		m_hInst,
		this
		)))
	{
		// log(failed ti window handle = null);
		return false;
	}

	static PIXELFORMATDESCRIPTOR pdf =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		m_bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	if (!(m_hDC = GetDC(m_hWindow)))
	{
		// log can't find a suitable pixelformat
		return false;
	}
	if (!(pixelFormat = ChoosePixelFormat(m_hDC, &pdf)))
	{
	}
}

bool Window::Update(Context& context)
{

}

bool Window::ShutDown()
{

}
