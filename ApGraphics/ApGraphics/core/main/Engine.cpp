#include "Engine.h"
#ifndef _DELETEMACRO_H
	#include "../../constants/deletemacros.h"
#endif

#ifndef _STRING_H
	#include "../../constants/string.h"
#endif

#include "../system/System.h"
#include "../system/Game.h"

EngineState Engine::m_EngineState = EngineState::Invalid;
Engine::Engine()
{
	m_EngineState = EngineState::Constructing;
}


Engine::~Engine()
{
	m_EngineState = EngineState::Destroying;
}

// Public Methods
int Engine::RunLoop()
{
	Context context;
	if (!this->Initialize())
	{
		return 0;
	}

	srand(GetTickCount());
	MSG msg = {};

	m_EngineState = EngineState::Runing;

	while (msg.message != WM_QUIT && m_EngineState == EngineState::Runing)
	{
		// check resize

		// 消息循环
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		this->Update(context);
		this->Draw(context);
	}

	// log(ending the program);
	// log to file();

	if (!this->ShutDown())
	{
		return 0;
	}
	return msg.wParam;
}

// Private methods
int Engine::Initialize()
{
	m_EngineState = EngineState::Initializing;
	Game* game = CreateGame();
	if (!game)
	{
		return false;
	}

	// add some system

	return true;
}

int Engine::Draw(const Context& context)
{
	return true;
}

int Engine::Update(const Context& context)
{
	return true;
}

int Engine::ShutDown()
{
	m_EngineState = EngineState::ShuttingDown;
	for (std::pair<SystemType, System*> psys : m_mapSystem)
	{
		//if (!psys.second->ShutDown())
		//{
			// log("failed to shutdown system:" + psys->GetSystemType());
		//	continue;
		//}
		SafeDelete(psys.second);
	}
	return true;
}

// 给引擎增加系统
int Engine::AddSystem(System* pSystem)
{
	auto element = m_mapSystem.insert(std::make_pair(pSystem->GetType(), pSystem));
	if (element.second)
	{
		return true;
	}
	return false;
}

// 创建游戏
Game* Engine::CreateGame()
{
	if (!AddSystem(new Game(GameData())))
	{
		return nullptr;
	}
	Game* game = GetSystem<Game>(SystemType::Sys_Game);
	if (!game)
	{
		return nullptr;
	}
	//if (!game->Initalize())
	//{
	//	return nullptr;
	//}

	return game;
}