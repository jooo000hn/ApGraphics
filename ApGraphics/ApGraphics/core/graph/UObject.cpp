#include "UObject.h"

int UObject::m_objectAmount = 0;
UObject::UObject(const std::tstring& name)
	:m_Name(name), m_ID(m_objectAmount), m_bIsInitialized(false)
	, m_bIsPostInitialized(false), m_bIsContentLoaded(false)
	, m_bIsPostContentLoaded(false), m_bIsDestroyed(false)
	, m_bCanTick(true), m_bCanDraw(true)
{
	++m_objectAmount;
}


UObject::UObject()
	:m_Name(std::tstring("")), m_ID(m_objectAmount), m_bIsInitialized(false)
	, m_bIsPostInitialized(false), m_bIsContentLoaded(false)
	, m_bIsPostContentLoaded(false), m_bIsDestroyed(false)
	, m_bCanTick(true), m_bCanDraw(true)
{
	m_Name = std::tstring("Object_") + TOSTRING(m_ID);
	++m_objectAmount;
}

UObject::~UObject()
{
	--m_objectAmount;
}

void UObject::Reset()
{

}
