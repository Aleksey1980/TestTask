// ServiceControlManager.cpp: реализация CServiceControlManager

#include "pch.h"
#include "ServiceControlManager.h"
#include "EnumService.h"
#include "Service.h"

// CServiceControlManager

STDMETHODIMP CServiceControlManager::Connect(const BSTR serverName)
{
	Disconnect();
	m_scm = OpenSCManager(serverName, SERVICES_ACTIVE_DATABASE, SC_MANAGER_CONNECT | SC_MANAGER_ENUMERATE_SERVICE);
	if (NULL == m_scm)
		return AtlHresultFromLastError();
	return S_OK;
}

STDMETHODIMP CServiceControlManager::Disconnect()
{
	if (NULL == m_scm)
		return S_FALSE;
	CloseServiceHandle(m_scm);
	m_scm = NULL;
	return S_OK;
}

STDMETHODIMP CServiceControlManager::GetServices(IEnumService** svcEnum)
{
	if (!IsConnected())
		return AtlHresultFromWin32(ERROR_INVALID_HANDLE);
	CEnumService* pEnum = new CEnumService(this);
	if (!pEnum->IsValid())
	{
		delete pEnum;
		*svcEnum = nullptr;
		return E_FAIL;
	}
	return pEnum->QueryInterface(__uuidof(IEnumService), reinterpret_cast<void**>(svcEnum));
}

STDMETHODIMP CServiceControlManager::GetService(const BSTR srvcName, IService** pService)
{
	if (!IsConnected())
		return AtlHresultFromWin32(ERROR_INVALID_HANDLE);
	CService* pSrvc = new CService(this, CComBSTR(srvcName));
	if (!pSrvc->IsValid())
	{
		HRESULT hr = pSrvc->lastResult();
		delete pSrvc;
		*pService = nullptr;
		return hr;
	}
	return pSrvc->QueryInterface(__uuidof(IService), reinterpret_cast<void**>(pService));
}

