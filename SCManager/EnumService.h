#pragma once

#include "resource.h"       // основные символы
#include "SCManager_i.h"
#include "InterfaceObject.h"
#include "ServiceControlManager.h"

class CEnumService :
	public CInterfacedObject<IEnumService>
{
public:
	CEnumService(CServiceControlManager* pMgr);

private:
	CServiceControlManager* m_manager;
	CHeapPtr<ENUM_SERVICE_STATUS_PROCESS> m_info;
	DWORD m_count;
	DWORD m_index;

public:
	inline bool IsValid() const
	{
		return m_info;
	}

	STDMETHOD(Clone(IEnumService** ppenum));
	STDMETHOD(Next(BSTR* name, BSTR* displayName));
	STDMETHOD(Reset());
	STDMETHOD(Skip(int celt));
};

