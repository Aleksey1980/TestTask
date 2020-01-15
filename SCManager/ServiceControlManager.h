// ServiceControlManager.h: объявление CServiceControlManager

#pragma once
#include "resource.h"       // основные символы
#include "SCManager_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CServiceControlManager

class ATL_NO_VTABLE CServiceControlManager :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CServiceControlManager, &CLSID_CoServiceControlManager>,
	public IServiceControlManager
{
public:
	CServiceControlManager()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(106)

	DECLARE_NOT_AGGREGATABLE(CServiceControlManager)

	BEGIN_COM_MAP(CServiceControlManager)
		COM_INTERFACE_ENTRY(IServiceControlManager)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		Disconnect();
	}

private:
	SC_HANDLE m_scm = NULL;

public:

	friend class CEnumService;
	friend class CService;

	inline bool IsConnected() const { return NULL != m_scm; }

	STDMETHOD(Connect(const BSTR serverName));
	STDMETHOD(Disconnect());
	STDMETHOD(GetServices(IEnumService** svcEnum));
	STDMETHOD(GetService(const BSTR srvcName, IService** pService));
};

OBJECT_ENTRY_AUTO(__uuidof(CoServiceControlManager), CServiceControlManager)
