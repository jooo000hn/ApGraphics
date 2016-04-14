#pragma once

#include <iostream>
#include <vector>
#include <functional>

class Listener
{
public:
	Listener(std::function<void(void*)>_func, std::string _Messagename)
	{
		m_Messagename = _Messagename;
		m_Func = _func;
	}

	~Listener()
	{

	}

	std::string getName()
	{
		return m_Messagename;
	}

	void listenerCallBack(void* _Args)
	{
		if (m_Func) {
			m_Func(_Args);
		}
	}

	std::function<void(void*)> getFunction()
	{
		return m_Func;
	}

	// 重载 "=="
	bool operator==(Listener* _observer) const
	{
		return m_Messagename == _observer->m_Messagename;
	}

private:
	std::string m_Messagename;        // 消息名称
	std::function<void(void*)> m_Func;  // 存储回调函数
};

class MessageMgr
{
protected:
	MessageMgr();
	~MessageMgr();

public:
	static MessageMgr* instance();

	// 增加观察者
	void addListener(std::function<void(void*)> _func, std::string _Messagename);

	// 移除观察者
	void removeListener(std::string _Messagename);

	// 清除观察者
	void removeAllListener();

	// 判断观察者是否已经添加过
	bool listenerExisted(std::function<void(void*)> _func, std::string _Messagename);

	// 发送消息
	void sendMessage(std::string _Messagename, void* _Args);
	void sendMessage(std::string _Messagename);

private:
	std::vector<Listener*> m_Array;
	static MessageMgr* m_Instance;
};