#ifndef _WINDOW_H
#define _WINDOW_H
#include "System.h"

// C runtime header files
#ifndef _WINDOWS_
	#include <windows.h>
#endif

#ifndef _CONTEXT_H
	#include "../../constants/context.h"
#endif
#ifndef _STRING_H
	#include "../../constants/string.h"
#endif

// ´°¿ÚÊý¾Ý
struct WindowData : public SystemData
{
	WindowData();
	WindowData(int width, int height, std::tstring& title = std::tstring("ApEngine"), int b = 32, bool fullScreen = false );

	int width;
	int height;
	int bits;
	std::tstring windowTitle;
	bool fullScreen;
};

struct ResizeData
{
	ResizeData();
	ResizeData(int resize, int newWidth, int newHeight);

	bool mustResize;

	int newWidth;
	int newHeight;
};

class Window : public System
{
	friend class Engine;
public:
	int GetWidth();
	int GetHeight();
	HWND GetWindowHandle();
	HDC GetDiviceContext();
	HINSTANCE GetInstance();
	ResizeData& GetResizeData() { return m_ResizeData; }
	LRESULT HandleEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	Window(const WindowData& data);
	virtual ~Window();
	virtual bool Initialize(); 
	virtual bool Update(Context& context); 
	virtual bool ShutDown();
private:
	bool CenterWindow();
	LRESULT CALLBACK Window_Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	ResizeData m_ResizeData;

	HWND m_hWindow;
	HDC m_hDC;
	HINSTANCE m_hInst;

	int m_Width;
	int m_Height;
	int m_bits;
	bool m_bFullScreen;
	std::tstring m_Title;
};

#endif // !_WINDOW_H
