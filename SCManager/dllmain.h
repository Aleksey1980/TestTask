// dllmain.h: объявление класса модуля.

class CSCManagerModule : public ATL::CAtlDllModuleT< CSCManagerModule >
{
public :
	DECLARE_LIBID(LIBID_SCManagerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SCMANAGER, "{fb0e622a-1061-461a-8b82-fa6036a1de65}")
};

extern class CSCManagerModule _AtlModule;
