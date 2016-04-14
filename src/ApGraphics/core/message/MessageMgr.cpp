#include "MessageMgr.h"

MessageMgr* MessageMgr::m_Instance = nullptr;
MessageMgr::MessageMgr()
{
	m_Array.clear();
}

MessageMgr::~MessageMgr()
{

}

MessageMgr* MessageMgr::instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new MessageMgr();
	}
	return m_Instance;
}

void MessageMgr::addListener(std::function<void(void*)> _func, std::string _Messagename)
{
	if (this->listenerExisted(_func, _Messagename))
	{
		return;
	}
	Listener* observer = new Listener(_func, _Messagename);
	m_Array.push_back(observer);
}

void MessageMgr::removeListener(std::string _Messagename)
{
	for (auto itor = m_Array.begin(); itor != m_Array.end();)
	{
		if (((*itor)->getName() == _Messagename))
		{
			delete *itor;
			itor = m_Array.erase(itor);
		}
		else
		{
			itor++;
		}
	}
}

void MessageMgr::removeAllListener()
{
	for (auto itor = m_Array.begin(); itor != m_Array.end();)
	{
		delete *itor;
		itor++;
	}
	m_Array.clear();
}

bool MessageMgr::listenerExisted(std::function<void(void*)> _func, std::string _Messagename)
{
	Listener* _observer = new Listener(_func, _Messagename);
	bool _existed = false;
	for (unsigned int i = 0; i < m_Array.size();i++)
	{
		auto item = m_Array[i];
		if (!item)
		{
			continue;
		}
		if (item == _observer)
		{
			_existed = true;
			break;
		}
	}
	delete _observer;
	return _existed;
}

void MessageMgr::sendMessage(std::string _Messagename, void* _Args)
{
	for (auto sp : m_Array)
	{
		if (sp->getName() == _Messagename)
		{
			sp->listenerCallBack(_Args);
		}
	}
}

void MessageMgr::sendMessage(std::string _Messagename)
{
	sendMessage(_Messagename, 0);
}
