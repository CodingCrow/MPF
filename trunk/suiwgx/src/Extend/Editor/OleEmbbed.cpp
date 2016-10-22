// ======================================================================
//
// Copyright (c) 2008-2012 ����, Inc. All rights reserved.
//
// suiwgx��Դ����ѭCPLЭ����п�Դ���κθ��˻�����������ʹ�ã������ܾ��ڴ˿������κ���ҵ���ʵĿ����롣
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// OleEmbbed.cpp

#include "stdafx.h"
#include <TOM.h>
#include "ReadStmOp.h"

#include <Extend/Editor/OleEmbbed.h>
#include <Extend/Editor/RichTextOleCallback.h>

#include <richedit/INC/richedit.h>
#include <richedit/src/textserv.h>

static suic::String SharpuiStmName = L"SharpuiStm";

static bool CreateNewStorageObject(IStorage** lpStg)
{
    const UINT flag = STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE;
    HRESULT lr = ::StgCreateDocfile(NULL, flag, 0 , lpStg);

    if (NOERROR == lr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------
// OleEmbbed

OleEmbbed::OleEmbbed()
{
	_refCount = 1;
    _isDirty = true;
}

OleEmbbed::~OleEmbbed()
{
}

HRESULT WINAPI OleEmbbed::QueryInterface(REFIID iid, void ** ppvObject)
{
	if (iid == IID_IUnknown || iid == IID_IOleObject)
	{
		*ppvObject = (IOleObject*)this;
		((IOleObject*)(*ppvObject))->AddRef();
		return S_OK;
	}
    else if (iid == IID_IOleCache)
    {
        *ppvObject = (IOleCache*)this;
		((IOleCache*)(*ppvObject))->AddRef();
		return S_OK;
    }
	else if (iid == IID_IViewObject || iid == IID_IViewObject2)
	{
		*ppvObject = (IViewObject2*)this;
		((IViewObject2*)(*ppvObject))->AddRef();
		return S_OK;
	}
    /*else if (iid == IID_IOleObjectCb)
    {
        *ppvObject = (IOleObjectCb*)this;
        ((IOleObjectCb *)(*ppvObject))->AddRef();
        return S_OK;
    }*/
    /*else if (iid == IID_IDataObject)
    {
        *ppvObject = (IDataObject*)this;
        ((IDataObject *)(*ppvObject))->AddRef();
        return S_OK;
    }*/
    else if (iid == IID_IPersistStorage)
    {
        *ppvObject = (IPersistStorage*)this;
        ((IPersistStorage *)(*ppvObject))->AddRef();
        return S_OK;
    }

	return E_NOINTERFACE;
}

ULONG WINAPI OleEmbbed::AddRef(void)
{
	_refCount++;
	return _refCount;
}

ULONG WINAPI OleEmbbed::Release(void)
{
	if (--_refCount == 0)
	{
		delete this;
		return 0;
	}

	return _refCount;
}

//---------------------------------------------------------
//
 HRESULT WINAPI OleEmbbed::GetClassID(CLSID *pClassID)
 {
     return GetUserClassID(pClassID);
 }

 // IOleCache
HRESULT WINAPI OleEmbbed::Cache(FORMATETC *pformatetc, DWORD advf,DWORD *pdwConnection)
{
    return S_OK;
}

HRESULT WINAPI OleEmbbed::Uncache(DWORD dwConnection)
{
    return S_OK;
}

HRESULT WINAPI OleEmbbed::EnumCache(IEnumSTATDATA **ppenumSTATDATA)
{
    return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::InitCache(IDataObject *pDataObject)
{
    return S_OK;
}

HRESULT WINAPI OleEmbbed::SetData(FORMATETC *pformatetc,STGMEDIUM *pmedium,BOOL fRelease)
{
    return S_OK;
}

 // IPersistStorage�ӿ�
 HRESULT WINAPI OleEmbbed::IsDirty(void)
 {
     return S_OK;
 }

 HRESULT WINAPI OleEmbbed::InitNew(IStorage *pStg)
 {
     return S_OK;
 }

 HRESULT WINAPI OleEmbbed::Load(IStorage *pStgSave)
 {
     //
     // �˺�����IStorage��ϵ�л����ݣ����¹��������Լ��Ķ���
     //
     StorageOp sOp(pStgSave);

     if (sOp.LocateReadStm(SharpuiStmName))
     {
         //
         // �˺����������Լ����������ϵ�л���IStorage���б���
         //
         if (LoadFromStream(&sOp))
         {
             return NOERROR;
         }
         else
         {
             return E_NOTIMPL;
         }
     }
     else
     {
         return E_NOTIMPL;
     }
 }

 HRESULT WINAPI OleEmbbed::Save(IStorage *pStgSave, BOOL fSameAsLoad)
 {
     /*if (!_isDirty)
     {
         return NOERROR;
     }*/

     StorageOp sOp(pStgSave);

     if (sOp.LocateWriteStm(SharpuiStmName))
     {
         //
         // �˺����������Լ����������ϵ�л���IStorage���б���
         //
         if (SaveToStream(&sOp))
         {
             return NOERROR;
         }
     }

     return E_NOTIMPL;
 }

 HRESULT WINAPI OleEmbbed::SaveCompleted(IStorage *pStgNew)
 {
     _isDirty = false;
     //
     // �򵥷���NOERROR��Ǳ�ʾ�Ѿ��ɹ�
     //
     return NOERROR;
 }

 HRESULT WINAPI OleEmbbed::HandsOffStorage(void)
 {
     return S_OK;
 }


//---------------------------------------------------------
//
HRESULT WINAPI OleEmbbed::SetClientSite(IOleClientSite *pClientSite)
{
	return S_OK;
}

HRESULT WINAPI OleEmbbed::GetClientSite(IOleClientSite **ppClientSite)
{
	return S_OK;
}

HRESULT WINAPI OleEmbbed::SetHostNames(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)
{
	return S_OK;
}

HRESULT WINAPI OleEmbbed::Close(DWORD dwSaveOption)
{
	return S_OK;
}

HRESULT WINAPI OleEmbbed::SetMoniker(DWORD dwWhichMoniker, IMoniker *pmk)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::InitFromData(IDataObject *pDataObject, BOOL fCreation, DWORD dwReserved)
{
	return S_OK;
}

HRESULT WINAPI OleEmbbed::GetClipboardData(DWORD dwReserved, IDataObject **ppDataObject)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::DoVerb(LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite, LONG lindex, HWND hwndParent, LPCRECT lprcPosRect)
{
	return S_OK;
}

HRESULT WINAPI OleEmbbed::EnumVerbs(IEnumOLEVERB **ppEnumOleVerb)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::Update(void)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::IsUpToDate(void)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::GetUserClassID(CLSID *pClsid)
{
	return S_OK;
}

HRESULT WINAPI OleEmbbed::GetUserType(DWORD dwFormOfType, LPOLESTR *pszUserType)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::SetExtent(DWORD dwDrawAspect, SIZEL *lpsizel)
{
    return S_OK;
}

HRESULT WINAPI OleEmbbed::GetExtent(DWORD dwDrawAspect, SIZEL *psizel)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::Advise(IAdviseSink *pAdvSink, DWORD *pdwConnection)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::Unadvise(DWORD dwConnection)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::EnumAdvise(IEnumSTATDATA **ppenumAdvise)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::GetMiscStatus(DWORD dwAspect, DWORD *pdwStatus)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::SetColorScheme(LOGPALETTE *pLogpal)
{
	return E_NOTIMPL;
}

static void __RenderBmp(HBITMAP hbmp, HDC hdc, suic::Rect rect)
{
    HDC hmem = ::CreateCompatibleDC(hdc);
    HBITMAP obmp = (HBITMAP)::SelectObject(hmem, hbmp);

    BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};

    int iMode = ::SetStretchBltMode(hdc, COLORONCOLOR);
    ::AlphaBlend(hdc, rect.left, rect.top, rect.Width(), rect.Height()
        , hmem, 0, 0, rect.Width(), rect.Height(), bf);

    ::SetStretchBltMode(hdc, iMode);
    ::SelectObject(hmem, obmp);

    ::DeleteDC(hmem);
}

HRESULT WINAPI OleEmbbed::Draw(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DVTARGETDEVICE *ptd,
							HDC hdcTargetDev, HDC hdcDraw, LPCRECTL lprcBounds, LPCRECTL lprcWBounds,
							BOOL ( WINAPI *pfnContinue )(ULONG_PTR dwContinue), ULONG_PTR dwContinue)
{
	if (lindex != -1)
    {
        return S_FALSE;
    }

    _rect.left = lprcBounds->left;
    _rect.top = lprcBounds->top;
    _rect.right = lprcBounds->right;
    _rect.bottom = lprcBounds->bottom;

    suic::Drawing* drawing = NULL;
    suic::RenderContext rCtx;
    suic::Rect rcDraw(0, 0, _rect.Width(), _rect.Height());

    drawing = rCtx.Open(_rect.Width(), _rect.Height(), 0);
    Render(drawing, rcDraw);

    // ���Ƶ�Richedit
    __RenderBmp(HANDLETOBITMAP(rCtx.bitmap->GetHandle()), hdcDraw, _rect);

	return S_OK;
}

HRESULT WINAPI OleEmbbed::GetColorSet(DWORD dwDrawAspect, LONG lindex, void *pvAspect, 
								   DVTARGETDEVICE *ptd, HDC hicTargetDev, LOGPALETTE **ppColorSet)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::Freeze(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DWORD *pdwFreeze)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::Unfreeze(DWORD dwFreeze)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::SetAdvise(DWORD aspects, DWORD advf, IAdviseSink *pAdvSink)
{
    if (NULL != pAdvSink)
    {
        RichEditOleCallback* txtHost = NULL;
        pAdvSink->QueryInterface(IID_IRichEditOleCallback, (void**)&txtHost);
        if (NULL != txtHost)
        {
            SetHolder(txtHost->GetHolder());
            txtHost->Release();
        }
    }
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::GetAdvise(DWORD *pAspects, DWORD *pAdvf, IAdviseSink **ppAdvSink)
{
	return E_NOTIMPL;
}

HRESULT WINAPI OleEmbbed::GetExtent(DWORD dwDrawAspect, LONG lindex, DVTARGETDEVICE *ptd, LPSIZEL lpsizel)
{
	return S_OK;
}
