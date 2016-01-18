#ifndef _ENGINE_H
#define _ENGINE_H

// C runtime files
#ifndef _WINDOWS_
	#include <windows.h>
#endif

#ifndef _MAP_
	#include <map>
#endif

#ifndef _CONTEXT_H
	#include "../../constants/context.h"
#endif

enum SystemType;

class System;
class Game;

// ����״̬
enum EngineState
{
	Invalid,
	Constructing,
	Initializing,
	Runing,
	ShuttingDown,
	Destroying
};

class Engine
{
public:
	Engine();
	~Engine();

	int RunLoop();

	//void *operator new(size_t size);
	//void operator delete(void* pdelete);

	// getter
	static EngineState GetEngineState() { return m_EngineState; }

private:
	int Initialize();
	int Draw(Context& context);
	int Update(Context& context);
	int ShutDown();

	// ����������ϵͳ
	int AddSystem(System* pSystem);
	
	template<typename T>
	T* GetSystem(SystemType systemType)
	{
		T* pSystem = static_cast<T*>(m_mapSystem[systemType]);
		if (!pSystem)
		{
			// Logger::log("system is not valid!");
			return nullptr;
		}
		return pSystem;
	}

	// ������Ϸ
	Game* CreateGame();

private:
	static EngineState m_EngineState;
	std::map<SystemType, System*> m_mapSystem;
};

#endif

