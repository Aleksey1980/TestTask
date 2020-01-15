#include "pch.h"
#include "Service.h"

void CALLBACK NotifyFunc(PVOID pParamtere)
{
	PSERVICE_NOTIFY_2 pNotify = reinterpret_cast<PSERVICE_NOTIFY_2>(pParamtere);
	if (pNotify->dwNotificationStatus == ERROR_SUCCESS)
	{
		CService* pService = reinterpret_cast<CService*>(pNotify->pContext);
		pService->NotifyServiceStatus(pNotify);
		if ((pNotify->dwNotificationTriggered && (SERVICE_NOTIFY_CREATED | SERVICE_NOTIFY_DELETED) == (SERVICE_NOTIFY_CREATED | SERVICE_NOTIFY_DELETED)))
			if (nullptr != pNotify->pszServiceNames)
				LocalFree(pNotify->pszServiceNames);
	}
}

DWORD WINAPI ThreadFunc(LPVOID lpThreadParams)
{
	CService* pService = reinterpret_cast<CService*>(lpThreadParams);
	pService->RequestNotifyServiceStatus();
	return 0;
}

bool CService::RequestNotifyServiceStatus()
{
	DWORD wrCallback = WAIT_OBJECT_0;
	while(true)
	{
		DWORD wrFinish = WaitForSingleObject(m_finish, 10);
		if (WAIT_OBJECT_0 == wrFinish || WAIT_FAILED == wrFinish)
			break;
		
		if (WAIT_OBJECT_0 == wrCallback)
		{
			m_notify.dwVersion = SERVICE_NOTIFY_STATUS_CHANGE;
			m_notify.pContext = this;
			m_notify.pfnNotifyCallback = &NotifyFunc;
			if (ERROR_SUCCESS != NotifyServiceStatusChange(
				m_service,
				SERVICE_NOTIFY_STOPPED | SERVICE_NOTIFY_START_PENDING | SERVICE_NOTIFY_STOP_PENDING | SERVICE_NOTIFY_RUNNING | SERVICE_NOTIFY_CONTINUE_PENDING | SERVICE_NOTIFY_PAUSE_PENDING | SERVICE_NOTIFY_PAUSED,
				&m_notify))
			{
				return false;
			}
		}
		wrCallback = WaitForSingleObjectEx(m_callback, INFINITE, TRUE);

		if (WAIT_FAILED == wrCallback)
			break;
	}
	return true;
}

void CService::NotifyServiceStatus(PSERVICE_NOTIFY pNotify)
{
	__try
	{
		if (m_status.dwCurrentState != pNotify->ServiceStatus.dwCurrentState)
		{			
			m_status.dwCurrentState = pNotify->ServiceStatus.dwCurrentState;
			if (m_notifyObject)
				m_notifyObject->StateChanged(pNotify->ServiceStatus.dwCurrentState);
		}
	}
	__finally
	{
		SetEvent(m_callback);
	}
}

CService::CService(CServiceControlManager* pMgr, CComBSTR& name) :
	CInterfacedObject(reinterpret_cast<void*>(pMgr)),
	m_manager(pMgr),
	m_service(NULL),
	m_notifyObject(nullptr),
	m_thread(NULL),
	m_callback(NULL),
	m_finish(NULL)
{
	if (m_manager->IsConnected())
	{
		m_service = OpenService(
			m_manager->m_scm,
			name.m_str,
			SERVICE_ALL_ACCESS
		);
		if (IsValid())
		{
			SERVICE_STATUS_PROCESS sp;
			DWORD bytesNeeded;
			if (QueryServiceStatusEx(m_service, SC_STATUS_PROCESS_INFO, (LPBYTE)&sp, sizeof(sp), &bytesNeeded))
				m_status.dwCurrentState = sp.dwCurrentState;
			m_callback.Attach(CreateEvent(nullptr, TRUE, FALSE, nullptr));
			m_finish.Attach(CreateEvent(nullptr, FALSE, FALSE, nullptr));
		}
	}
}

CService::~CService()
{
	SetNotifyObject(nullptr);
	if (NULL != m_service)
		CloseServiceHandle(m_service);
}

STDMETHODIMP CService::GetConfig(int* pType, int* pStart, BSTR* ppBinaryPath, BSTR* ppStartName)
{
	if (!IsValid())
		return AtlHresultFromWin32(ERROR_INVALID_HANDLE);
	DWORD temp;
	bool b = QueryServiceConfig(m_service, nullptr, NULL, &temp);
	DWORD err = GetLastError();
	if (!b && ERROR_INSUFFICIENT_BUFFER == err)
	{
		CHeapPtr<BYTE> buffer;
		if (!buffer.AllocateBytes(temp))
			return AtlHresultFromWin32(E_OUTOFMEMORY);
		if (!QueryServiceConfig(m_service, (LPQUERY_SERVICE_CONFIG)buffer.m_pData, temp, &temp))
			return AtlHresultFromLastError();
		LPQUERY_SERVICE_CONFIG pConfig = (LPQUERY_SERVICE_CONFIG)buffer.m_pData;
		*pType = pConfig->dwServiceType;
		*pStart = pConfig->dwStartType;
		*ppBinaryPath = CComBSTR(pConfig->lpBinaryPathName).Detach();
		*ppStartName = CComBSTR(pConfig->lpServiceStartName).Detach();
		return S_OK;
	}
	else
		return AtlHresultFromWin32(err);
}


STDMETHODIMP CService::GetCurrentState(int* pState)
{
	if (!IsValid())
		return AtlHresultFromWin32(ERROR_INVALID_HANDLE);
	if (!m_thread)
	{
		SERVICE_STATUS_PROCESS sp;
		DWORD bytesNeeded;
		if (!QueryServiceStatusEx(m_service, SC_STATUS_PROCESS_INFO, (LPBYTE)&sp, sizeof(sp), &bytesNeeded))
			return AtlHresultFromLastError();
		m_status.dwCurrentState = sp.dwCurrentState;
	}
	*pState = m_status.dwCurrentState;
	return S_OK;
}

STDMETHODIMP CService::Start()
{
	if (!IsValid())
		return AtlHresultFromWin32(ERROR_INVALID_HANDLE);
	if (!StartService(m_service, NULL, nullptr))
		return AtlHresultFromLastError();
	return S_OK;
}

STDMETHODIMP CService::Stop()
{
	if (!IsValid())
		return AtlHresultFromWin32(ERROR_INVALID_HANDLE);
	if (!ControlService(m_service, SERVICE_CONTROL_STOP, &m_status))
		return AtlHresultFromLastError();
	return S_OK;
}

STDMETHODIMP CService::Pause()
{
	if (!IsValid())
		return AtlHresultFromWin32(ERROR_INVALID_HANDLE);
	if (!ControlService(m_service, SERVICE_CONTROL_PAUSE, &m_status))
		return AtlHresultFromLastError();
	return S_OK;
}

STDMETHODIMP CService::Continue()
{
	if (!IsValid())
		return AtlHresultFromWin32(ERROR_INVALID_HANDLE);
	if (!ControlService(m_service, SERVICE_CONTROL_CONTINUE, &m_status))
		return AtlHresultFromLastError();
	return S_OK;
}

STDMETHODIMP CService::SetNotifyObject(IServiceNotify* pNotify)
{
	if (!IsValid())
		return AtlHresultFromWin32(ERROR_INVALID_HANDLE);
	if (m_notifyObject != pNotify)
	{
		if (m_thread)
		{
			SetEvent(m_finish);
			SetEvent(m_callback);
			WaitForSingleObjectEx(m_thread, INFINITE, TRUE);
			m_thread.Close();
		}
		m_notifyObject = pNotify;
		if (m_notifyObject)
		{
			ResetEvent(m_finish);
			DWORD temp;
			m_thread.Attach(CRTThreadTraits::CreateThread(nullptr, 0, ThreadFunc, this, 0, &temp));
			if (!m_thread)
				return AtlHresultFromLastError();
		}
	}
	return S_OK;
}
