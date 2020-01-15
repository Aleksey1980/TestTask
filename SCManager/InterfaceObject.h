#pragma once

#include <atlbase.h>

template <class Intf>
class CInterfacedObject :
	public Intf
{
	typedef typename Intf Interface;
private:
	ULONG m_refCount;
	ATL::CComPtr<IUnknown> m_outer;

public:
	CInterfacedObject(void* pv): 
		m_outer(reinterpret_cast<IUnknown*>(pv))
	{

	}

	virtual ~CInterfacedObject()
	{

	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override
	{
		if (IsEqualIID(riid, __uuidof(IUnknown)))
		{
			*ppvObject = dynamic_cast<IUnknown*>(this);
			AddRef();
			return S_OK;
		}
		if (IsEqualIID(riid, __uuidof(Interface)))
		{
			*ppvObject = dynamic_cast<Interface*>(this);
			AddRef();
			return S_OK;
		}
		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef(void) override
	{
		return InterlockedIncrement(&m_refCount);
	}

	ULONG STDMETHODCALLTYPE Release(void) override
	{
		ULONG ref = InterlockedDecrement(&m_refCount);
		if (0 == m_refCount)
		{
			delete this;
			return 0;
		}
		return m_refCount;
	}
};
