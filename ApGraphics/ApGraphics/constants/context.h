#ifndef _CONTEXT_H
#define _CONTEXT_H

class Window;

// Defines
#define WINDOW (context.pWnd)

struct Context
{
	float dTime;

	Window* pWnd;
};

#endif // !_CONTEXT_H
