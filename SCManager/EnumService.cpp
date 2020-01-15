#include "pch.h"
#include "EnumService.h"

CEnumService::CEnumService(CServiceControlManager* pMgr) :
	CInterfacedObject(dynamic_cast<IUnknown*>(pMgr)),
	m_manager(pMgr),
	m_info(nullptr),
	m_count(0),
	m_index(0)
{
	DWORD bytesNeeded = 0;

	if (m_manager->IsConnected())
	{
		bool b = EnumServicesStatusEx(
			m_manager->m_scm,
			SC_ENUM_PROCESS_INFO,
			SERVICE_WIN32,
			SERVICE_STATE_ALL,
			nullptr,
			0,
			&bytesNeeded,
			&m_count,
			nullptr,
			nullptr
		);

		if (!b && GetLastError() == ERROR_MORE_DATA)
		{
			if (m_info.AllocateBytes(bytesNeeded))
			{
				if (!EnumServicesStatusEx(
					m_manager->m_scm,
					SC_ENUM_PROCESS_INFO,
					SERVICE_WIN32,
					SERVICE_STATE_ALL,
					(LPBYTE)m_info.m_pData,
					bytesNeeded,
					&bytesNeeded,
					&m_count,
					nullptr,
					nullptr
				))
				{
					m_info.Free();
					m_count = 0;
				}
			}
		}
	}
}


STDMETHODIMP CEnumService::Clone(IEnumService** ppenum)
{
	if (NULL == m_manager)
		return E_POINTER;
	CEnumService* pEnum = new CEnumService(m_manager);
	if (!pEnum->IsValid())
	{
		delete pEnum;
		return E_FAIL;
	}
	return pEnum->QueryInterface(__uuidof(IEnumService), reinterpret_cast<void**>(ppenum));
}

STDMETHODIMP CEnumService::Next(BSTR* name, BSTR* displayName)
{
	if (m_index >= m_count)
	{
		*name = nullptr;
		*displayName = nullptr;
		return S_FALSE;
	}
	*name = CComBSTR(m_info.m_pData[m_index].lpServiceName).Detach();
	*displayName = CComBSTR(m_info.m_pData[m_index].lpDisplayName).Detach();
	m_index++;
	return S_OK;
}

STDMETHODIMP CEnumService::Reset()
{
	m_index = 0;
	return S_OK;
}

STDMETHODIMP CEnumService::Skip(int celt)
{
	m_index += celt;
	if (m_index > m_count)
	{
		m_index = m_count;
		return S_FALSE;
	}
	return S_OK;
}
