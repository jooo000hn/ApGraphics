#include "Window.h"

WindowData::WindowData()
	:SystemData(SystemType::Sys_Window)
	, width(-1), height(-1)
	, bits(-1), windowTitle(_T(""))
	, fullScreen(false)
{

}

WindowData::WindowData(int width, int height, const std::tstring& title /*= std::tstring("ApEngine")*/, int b /*= 32*/, bool fullScreen /*= false */)
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

ResizeData::ResizeData(bool resize, int newWidth, int newHeight)
	: mustResize(resize)
	, newWidth(newWidth)
	, newHeight(newHeight)
{

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
	{
		// 从lparam中取出已保留的window的this指针
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
	return DefWindowProc(hWnd, msg, wParam, lParam);
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
		return 0;
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);

		m_ResizeData.mustResize = true;
		m_ResizeData.newWidth = width;
		m_ResizeData.newHeight = height;
	}
		return 0;
	case WM_DISPLAYCHANGE:
	{
		InvalidateRect(hWnd, NULL, FALSE);
	}
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
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
	, m_Bits(data.bits)
	, m_bFullScreen(data.fullScreen)
	, m_Title(data.windowTitle)
	, m_ResizeData()
{

}

Window::~Window()
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
	wndClass.lpszClassName = className.c_str();

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
		dmScreenSettings.dmBitsPerPel = m_Bits;
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

	if (!(m_hWindow = CreateWindowEx(
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
		this   // 把指向当前创建的窗口指针保留到userdata
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
		m_Bits,
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
		// log can't create device context
		return false;
	}
	if (!(pixelFormat = ChoosePixelFormat(m_hDC, &pdf)))
	{
		// log can't find a suitable pixelformat
		return false;
	}
	if (!SetPixelFormat(m_hDC, pixelFormat, &pdf))
	{
		// log can't set the pixelformat
		return false;
	}

	ShowWindow(m_hWindow, SW_SHOW);

	// 窗口获得焦点
	SetForegroundWindow(m_hWindow); 
	SetFocus(m_hWindow);

	m_ResizeData.mustResize = true;
	m_ResizeData.newWidth = m_Width;
	m_ResizeData.newHeight = m_Height;
	if (!this->CenterWindow())
	{
		// log failed to center window
		return false;
	}

	HWND hConsoledWnd = GetConsoleWindow();
	if (hConsoledWnd != NULL)
	{
		HMENU hConsoledMenu = GetSystemMenu(hConsoledWnd, FALSE);
		if (hConsoledMenu != 0)
		{
			// 移除关闭按钮
			BOOL bRet = RemoveMenu(hConsoledMenu, SC_CLOSE, MF_BYCOMMAND);
			if (!bRet)
			{
				// log failed to remove close button
				return false;
			}
		}
	}
	// log window is initialized

	// 创建窗口成功
	return true;
}

bool Window::Update(Context& context)
{
	System::Update(context);
	if (WINDOW != this)
	{
		WINDOW = this;
	}
	return true;
}

bool Window::ShutDown()
{
	System::ShutDown();
	if (m_bFullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}

	// 销毁DC
	if (m_hDC && !ReleaseDC(m_hWindow, m_hDC))
	{
		//Logger::Log(_T("Release DC failed"));
		m_hDC = NULL;
		return false;
	}
	
	// 销毁window
	if (m_hWindow && !DestroyWindow(m_hWindow))
	{
		//Logger::Log(_T("Could not destroy the window"));
		m_hWindow = NULL;
		return false;
	}

	// 注销类
	if (!UnregisterClass(m_Title.c_str(), m_hInst))
	{
		//Logger::Log(_T("Could not unregister class"));
		m_hInst = NULL;
		return false;
	}

	return true;
}

bool Window::CenterWindow()
{
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;       // Window Extended Style
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;						// Windows Style

	RECT R = { 0, 0, m_Width, m_Height };

	AdjustWindowRectEx(&R, dwStyle, false, dwExStyle);

	int windowwidth = R.right - R.left;
	int windowheight = R.bottom - R.top;

	int posx = GetSystemMetrics(SM_CXSCREEN) / 2 - windowwidth / 2;
	int posy = GetSystemMetrics(SM_CYSCREEN) / 2 - windowheight / 2;

	// 窗口位于屏幕中心
	if (SetWindowPos(m_hWindow, NULL, posx, posy, windowwidth, windowheight, SWP_SHOWWINDOW) == NULL)
		return false;

	return true;
}

LRESULT CALLBACK Window::Window_Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
