#pragma once

#include "resource.h"       // �������� �������
#include "SCManager_i.h"
#include "InterfaceObject.h"
#include "ServiceControlManager.h"


class CService :
	public CInterfacedObject<IService>
{
	friend void CALLBACK NotifyFunc(PVOID pParamtere);
	friend DWORD WINAPI ThreadFunc(LPVOID lpThreadParams);

private:
	CServiceControlManager* m_manager;
	SC_HANDLE m_service;
	SERVICE_STATUS m_status;
	CComPtr<IServiceNotify> m_notifyObject;
	CHandle m_thread;
	CHandle m_callback;
	CHandle m_finish;
	SERVICE_NOTIFY m_notify;

	bool RequestNotifyServiceStatus();
	void NotifyServiceStatus(PSERVICE_NOTIFY pNotify);

public:
	CService(CServiceControlManager* pMgr, CComBSTR& name);
	~CService();

	inline bool IsValid() const { return NULL != m_service; }

	STDMETHOD(GetConfig(int* pType, int* pStart, BSTR* ppBinaryPth, BSTR* ppStartName));
	STDMETHOD(GetCurrentState(int* pState));
	STDMETHOD(Start());
	STDMETHOD(Stop());
	STDMETHOD(Pause());
	STDMETHOD(Continue());
	STDMETHOD(SetNotifyObject(IServiceNotify* pNotify));
};

