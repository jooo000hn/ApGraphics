#include "WinMain.h"

// additional include files
#ifndef _STRING_H
	#include "../../constants/string.h"
#endif
#ifndef _IOSTREAM_H
	#include "../../constants/iostream.h"
#endif
#ifndef _DELETEMACRO_H
	#include "../../constants/deletemacros.h"
#endif

#include "engine.h"

#if defined (DEBUG) | defined(_DEBUG)
int _tmain(int argc, char* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	// logger::log(starting the program);

	// run main function
	WinMain((HINSTANCE)GetModuleHandle(NULL), 0, 0, SW_SHOW);
}
#endif // (DEBUG) | defined(_DEBUG)

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdline);
	UNREFERENCED_PARAMETER(nCmdShow);

#if defined (DEBUG) | defined(_DEBUG)
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// enable tun time memory leak check debug builds
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(0);
#endif
	// Create the engine
	Engine * pEngine = new Engine();

	// kick of the game
	int result = pEngine->RunLoop();

	// Delete the engine
	SafeDelete(pEngine);

	return result;
}