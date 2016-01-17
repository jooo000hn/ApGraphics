#ifndef _WINMAIN_H
#define _WINMAIN_H

// C runtime header files
#ifndef _WINDOWS_
	#include <windows.h>
#endif // !_WINDOW_

int _tmain(int argc, char* argv[]);
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow);

#endif // !_WINMAIN_H
