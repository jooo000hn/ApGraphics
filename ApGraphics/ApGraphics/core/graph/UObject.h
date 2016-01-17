#ifndef _UOBJECT_H
#define _UOBJECT_H

#ifndef _CONTEXT_H
	#include "../../constants/context.h"
#endif
#ifndef _STRING_H
	#include "../../constants/string.h"
#endif

class UObject
{
public:
	UObject();
	UObject(const std::tstring& name);
	virtual ~UObject();

	//void* operator new (size_t size);
	//void operator delete(void* pdelete);

	virtual bool Initialize()							{ m_bIsInitialized = true; return true; }
	virtual bool PostInitialize()						{ m_bIsPostInitialized = true; return true; }
	virtual bool LoadContent()							{ m_bIsContentLoaded = true; return true; }
	virtual bool PostLoadContent()						{ m_bIsPostContentLoaded = true; return true; }
	virtual bool Update(Context& context)				{ return true; }
	// virtual bool LateUpdate()						{ return true; }
	virtual bool Draw(Context& context)					{ return true; }
	virtual bool DrawUI(Context& context)				{ return true; }
	virtual bool ShutDown()								{ return true; }

	virtual void Reset();

	void setName(const std::tstring& name) { m_Name = name; }
	const std::tstring& GetName() { return m_Name; }

	bool IsInitialized() const { return m_bIsInitialized; }
	bool IsPostInitialized() const { return m_bIsPostInitialized; }
	bool IsContentLoaded() const { return m_bIsContentLoaded; }
	bool IsPostContentLoaded() const { return m_bIsPostContentLoaded; }

	void SetCanTick(bool canTick) { m_bCanTick = canTick; }
	bool CanTick() const { return m_bCanTick; }
	void SetCanDraw(bool canDraw) { m_bCanDraw = canDraw; }
	bool CanDraw() const { return m_bCanDraw; }

	void Destroy() { m_bIsDestroyed = true; }
	bool IsDestroyed() { return m_bIsDestroyed; }

	void Activate() { m_bIsActivated = true; }
	void DeActivate() { m_bIsActivated = false; }
	bool IsActivate() { return m_bIsActivated; }

protected:
	static int m_objectAmount;
	int m_ID;

	bool m_bIsInitialized;
	bool m_bIsPostInitialized;
	bool m_bIsContentLoaded;
	bool m_bIsPostContentLoaded;

	std::tstring m_Name;

private:
	bool m_bIsActivated;
	bool m_bIsDestroyed;
	bool m_bCanTick;
	bool m_bCanDraw;
};

#endif // !_UOBJECT_H
