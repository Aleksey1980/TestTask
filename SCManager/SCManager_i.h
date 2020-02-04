

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for SCManager.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __SCManager_i_h__
#define __SCManager_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IServiceNotify_FWD_DEFINED__
#define __IServiceNotify_FWD_DEFINED__
typedef interface IServiceNotify IServiceNotify;

#endif 	/* __IServiceNotify_FWD_DEFINED__ */


#ifndef __IService_FWD_DEFINED__
#define __IService_FWD_DEFINED__
typedef interface IService IService;

#endif 	/* __IService_FWD_DEFINED__ */


#ifndef __IEnumService_FWD_DEFINED__
#define __IEnumService_FWD_DEFINED__
typedef interface IEnumService IEnumService;

#endif 	/* __IEnumService_FWD_DEFINED__ */


#ifndef __IServiceControlManager_FWD_DEFINED__
#define __IServiceControlManager_FWD_DEFINED__
typedef interface IServiceControlManager IServiceControlManager;

#endif 	/* __IServiceControlManager_FWD_DEFINED__ */


#ifndef __CoServiceControlManager_FWD_DEFINED__
#define __CoServiceControlManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoServiceControlManager CoServiceControlManager;
#else
typedef struct CoServiceControlManager CoServiceControlManager;
#endif /* __cplusplus */

#endif 	/* __CoServiceControlManager_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __SCManagerLib_LIBRARY_DEFINED__
#define __SCManagerLib_LIBRARY_DEFINED__

/* library SCManagerLib */
/* [version][uuid] */ 

/* [uuid] */ 
enum  DECLSPEC_UUID("F377F7F8-324C-4956-850B-F8BA3E1F0F9D") ServiceType
    {
        KernelDriver	= 1,
        FileSystemDrive	= 2,
        Win32OwnProcess	= 0x10,
        Win32ShareProcess	= 0x20
    } ;
/* [uuid] */ 
enum  DECLSPEC_UUID("FF975FF5-4A10-4573-90A0-F0FB4542515C") ServiceState
    {
        ContinuePending	= 0x5,
        PausePending	= 0x6,
        Paused	= 0x7,
        Running	= 0x4,
        StartPending	= 0x2,
        StopPending	= 0x3,
        Stopped	= 0x1
    } ;
/* [uuid] */ 
enum  DECLSPEC_UUID("8C2EA04C-50C0-445F-A7C7-B568468411FA") ServiceStartType
    {
        Automatic	= 0x2,
        Boot	= 0,
        Demand	= 0x3,
        Disabled	= 0x4,
        System	= 0x1
    } ;
/* [uuid] */ 
enum  DECLSPEC_UUID("85C2BE6F-CFC6-41E6-A2BC-C46610A9C335") ServiceAcceptingControl
    {
        Stop	= 0x1,
        PauseContinue	= 0x2,
        Shutdown	= 0x4,
        ParamChange	= 0x8,
        NetBindChange	= 0x10,
        HardwareProfileChange	= 0x20,
        PowerEvent	= 0x40,
        SessionChange	= 0x80,
        PreShutdown	= 0x100,
        TimeChange	= 0x200,
        TriggerEvent	= 0x400,
        UserLogoff	= 0x800
    } ;

EXTERN_C const IID LIBID_SCManagerLib;

#ifndef __IServiceNotify_INTERFACE_DEFINED__
#define __IServiceNotify_INTERFACE_DEFINED__

/* interface IServiceNotify */
/* [object][uuid] */ 


EXTERN_C const IID IID_IServiceNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6AFD0DAB-8F44-4CB1-9345-28EF8D8C5F76")
    IServiceNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StateChanged( 
            /* [in] */ long newState,
            /* [in] */ long acceptControl) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IServiceNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServiceNotify * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServiceNotify * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServiceNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *StateChanged )( 
            IServiceNotify * This,
            /* [in] */ long newState,
            /* [in] */ long acceptControl);
        
        END_INTERFACE
    } IServiceNotifyVtbl;

    interface IServiceNotify
    {
        CONST_VTBL struct IServiceNotifyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServiceNotify_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServiceNotify_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServiceNotify_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServiceNotify_StateChanged(This,newState,acceptControl)	\
    ( (This)->lpVtbl -> StateChanged(This,newState,acceptControl) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IServiceNotify_INTERFACE_DEFINED__ */


#ifndef __IService_INTERFACE_DEFINED__
#define __IService_INTERFACE_DEFINED__

/* interface IService */
/* [object][uuid] */ 


EXTERN_C const IID IID_IService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3FA76749-680A-4B3C-9667-4238F03FB94B")
    IService : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetConfig( 
            /* [out] */ long *pType,
            /* [out] */ long *pStart,
            /* [out] */ BSTR *ppBinaryPath,
            /* [out] */ BSTR *ppStartName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentState( 
            /* [out] */ long *pState,
            /* [out] */ long *pAcceptControl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Continue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNotifyObject( 
            /* [in] */ IServiceNotify *pNotify) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IService * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IService * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IService * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfig )( 
            IService * This,
            /* [out] */ long *pType,
            /* [out] */ long *pStart,
            /* [out] */ BSTR *ppBinaryPath,
            /* [out] */ BSTR *ppStartName);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentState )( 
            IService * This,
            /* [out] */ long *pState,
            /* [out] */ long *pAcceptControl);
        
        HRESULT ( STDMETHODCALLTYPE *Start )( 
            IService * This);
        
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IService * This);
        
        HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IService * This);
        
        HRESULT ( STDMETHODCALLTYPE *Continue )( 
            IService * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetNotifyObject )( 
            IService * This,
            /* [in] */ IServiceNotify *pNotify);
        
        END_INTERFACE
    } IServiceVtbl;

    interface IService
    {
        CONST_VTBL struct IServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IService_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IService_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IService_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IService_GetConfig(This,pType,pStart,ppBinaryPath,ppStartName)	\
    ( (This)->lpVtbl -> GetConfig(This,pType,pStart,ppBinaryPath,ppStartName) ) 

#define IService_GetCurrentState(This,pState,pAcceptControl)	\
    ( (This)->lpVtbl -> GetCurrentState(This,pState,pAcceptControl) ) 

#define IService_Start(This)	\
    ( (This)->lpVtbl -> Start(This) ) 

#define IService_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#define IService_Pause(This)	\
    ( (This)->lpVtbl -> Pause(This) ) 

#define IService_Continue(This)	\
    ( (This)->lpVtbl -> Continue(This) ) 

#define IService_SetNotifyObject(This,pNotify)	\
    ( (This)->lpVtbl -> SetNotifyObject(This,pNotify) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IService_INTERFACE_DEFINED__ */


#ifndef __IEnumService_INTERFACE_DEFINED__
#define __IEnumService_INTERFACE_DEFINED__

/* interface IEnumService */
/* [object][uuid] */ 


EXTERN_C const IID IID_IEnumService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("887BDF0A-ED76-4014-9DAC-5890F41FF7A2")
    IEnumService : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumService **ppenum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [out] */ BSTR *pName,
            /* [out] */ BSTR *pDisplayName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            int celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumService * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumService * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumService * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumService * This,
            /* [out] */ IEnumService **ppenum);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumService * This,
            /* [out] */ BSTR *pName,
            /* [out] */ BSTR *pDisplayName);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumService * This);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumService * This,
            int celt);
        
        END_INTERFACE
    } IEnumServiceVtbl;

    interface IEnumService
    {
        CONST_VTBL struct IEnumServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumService_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumService_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumService_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumService_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IEnumService_Next(This,pName,pDisplayName)	\
    ( (This)->lpVtbl -> Next(This,pName,pDisplayName) ) 

#define IEnumService_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumService_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumService_INTERFACE_DEFINED__ */


#ifndef __IServiceControlManager_INTERFACE_DEFINED__
#define __IServiceControlManager_INTERFACE_DEFINED__

/* interface IServiceControlManager */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IServiceControlManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("408e8eff-5331-4eaa-955c-af5974a61929")
    IServiceControlManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            const BSTR serverName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetServices( 
            /* [out] */ IEnumService **svcEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetService( 
            const BSTR srvcName,
            /* [out] */ IService **pService) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IServiceControlManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServiceControlManager * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServiceControlManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServiceControlManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IServiceControlManager * This,
            const BSTR serverName);
        
        HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IServiceControlManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetServices )( 
            IServiceControlManager * This,
            /* [out] */ IEnumService **svcEnum);
        
        HRESULT ( STDMETHODCALLTYPE *GetService )( 
            IServiceControlManager * This,
            const BSTR srvcName,
            /* [out] */ IService **pService);
        
        END_INTERFACE
    } IServiceControlManagerVtbl;

    interface IServiceControlManager
    {
        CONST_VTBL struct IServiceControlManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServiceControlManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServiceControlManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServiceControlManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServiceControlManager_Connect(This,serverName)	\
    ( (This)->lpVtbl -> Connect(This,serverName) ) 

#define IServiceControlManager_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#define IServiceControlManager_GetServices(This,svcEnum)	\
    ( (This)->lpVtbl -> GetServices(This,svcEnum) ) 

#define IServiceControlManager_GetService(This,srvcName,pService)	\
    ( (This)->lpVtbl -> GetService(This,srvcName,pService) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IServiceControlManager_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CoServiceControlManager;

#ifdef __cplusplus

class DECLSPEC_UUID("472ca3cc-c5a8-4b31-8a55-1cb2a85aa5ca")
CoServiceControlManager;
#endif
#endif /* __SCManagerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


