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

	// ���� "=="
	bool operator==(Listener* _observer) const
	{
		return m_Messagename == _observer->m_Messagename;
	}

private:
	std::string m_Messagename;        // ��Ϣ����
	std::function<void(void*)> m_Func;  // �洢�ص�����
};

class MessageMgr
{
protected:
	MessageMgr();
	~MessageMgr();

public:
	static MessageMgr* instance();

	// ���ӹ۲���
	void addListener(std::function<void(void*)> _func, std::string _Messagename);

	// �Ƴ��۲���
	void removeListener(std::string _Messagename);

	// ����۲���
	void removeAllListener();

	// �жϹ۲����Ƿ��Ѿ���ӹ�
	bool listenerExisted(std::function<void(void*)> _func, std::string _Messagename);

	// ������Ϣ
	void sendMessage(std::string _Messagename, void* _Args);
	void sendMessage(std::string _Messagename);

private:
	std::vector<Listener*> m_Array;
	static MessageMgr* m_Instance;
};