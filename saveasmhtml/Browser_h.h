
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Sep 02 10:07:36 2002
 */
/* Compiler settings for Browser.odl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __Browser_h_h__
#define __Browser_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBrowser_FWD_DEFINED__
#define __IBrowser_FWD_DEFINED__
typedef interface IBrowser IBrowser;
#endif 	/* __IBrowser_FWD_DEFINED__ */


#ifndef __Document_FWD_DEFINED__
#define __Document_FWD_DEFINED__

#ifdef __cplusplus
typedef class Document Document;
#else
typedef struct Document Document;
#endif /* __cplusplus */

#endif 	/* __Document_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __Browser_LIBRARY_DEFINED__
#define __Browser_LIBRARY_DEFINED__

/* library Browser */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_Browser,0x41B33A52,0x710C,0x11D3,0xBB,0x8B,0x00,0xC0,0x4F,0xA3,0x47,0x1C);

#ifndef __IBrowser_DISPINTERFACE_DEFINED__
#define __IBrowser_DISPINTERFACE_DEFINED__

/* dispinterface IBrowser */
/* [uuid] */ 


DEFINE_GUID(DIID_IBrowser,0x41B33A53,0x710C,0x11D3,0xBB,0x8B,0x00,0xC0,0x4F,0xA3,0x47,0x1C);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("41B33A53-710C-11D3-BB8B-00C04FA3471C")
    IBrowser : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrowser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrowser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrowser * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBrowser * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBrowser * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBrowser * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBrowser * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IBrowserVtbl;

    interface IBrowser
    {
        CONST_VTBL struct IBrowserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBrowser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBrowser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBrowser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBrowser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBrowser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBrowser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IBrowser_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Document,0x41B33A51,0x710C,0x11D3,0xBB,0x8B,0x00,0xC0,0x4F,0xA3,0x47,0x1C);

#ifdef __cplusplus

class DECLSPEC_UUID("41B33A51-710C-11D3-BB8B-00C04FA3471C")
Document;
#endif
#endif /* __Browser_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


